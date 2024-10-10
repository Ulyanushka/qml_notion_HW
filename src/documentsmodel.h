#ifndef DOCUMENTSMODEL_H
#define DOCUMENTSMODEL_H

#include <QAbstractListModel>
#include <QQmlEngine>
#include <QVariant>


class Block : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    enum BlockType {
        Mesh,
        H1Title,
        H2Title,
        H3Title,
        Italic,
        Bold,
        Underline,
        Link,
        Image,
        BulletList,
        NumberedList,
        HorizontalLine,
        Blockquote,
        InlineBlock, //no langs include
        CodeBlock, //no langs include
        GitHubTables,
        GitHubTasks,
        Tags, //hidden
        QtQuickMediaPLayer,
        HTML4Subset //stansart tool
    };
    Q_ENUM(BlockType)

    Block(const BlockType& type, const QVariant& content, QObject* parent = nullptr);

    Q_INVOKABLE QString GetTitle() const { return title_; }
    Q_INVOKABLE BlockType GetType() const { return type_; }
    Q_INVOKABLE QVariant GetContent() const { return content_; }

private:
    QString title_;
    BlockType type_;
    QVariant content_;
};


class NotionDocument : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    NotionDocument(const QString& title, const QString& file_path);

    Q_INVOKABLE QString GetTitle() const { return title_; }
    Q_INVOKABLE QList<Block*> GetBlocks() const { return blocks_; }
    Q_INVOKABLE Block* GetBlock(const int id) const;

private:
    void SetBlocks(const QString& file_path);

    QString title_;
    //QString file_path_;
    QList<Block*> blocks_;
};


class TreeItem
{
public:
    explicit TreeItem(const QString& title, TreeItem* parent = nullptr)
        : title_(title), parent_(parent) {}

    TreeItem* parent() { return parent_; }
    TreeItem* child(int row) { return (row >= 0 && row < childCount()) ? children_.at(row).get() : nullptr; }
    void appendChild(std::unique_ptr<TreeItem>&& child) { children_.push_back(std::move(child)); }
    int childCount() const { return int(children_.size()); }

    QString data() const { return title_; }
    int row() const;

private:
    TreeItem* parent_;
    std::vector<std::unique_ptr<TreeItem>> children_;
    QString title_;
};


class DocumentsTreeModel : public QAbstractItemModel
{
    Q_OBJECT
    QML_ELEMENT

public:
    Q_DISABLE_COPY_MOVE(DocumentsTreeModel)

    explicit DocumentsTreeModel(const QList<NotionDocument*> documents, QObject* parent = nullptr);
    ~DocumentsTreeModel() override = default;

    Q_INVOKABLE QVariant data(const QModelIndex& index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column, const QModelIndex& parent = {}) const override;
    Q_INVOKABLE QModelIndex parent(const QModelIndex& index) const override;

    int rowCount(const QModelIndex& parent = {}) const override;
    int columnCount(const QModelIndex& parent = {}) const override { return 1; }

    Q_INVOKABLE QStringList GetPath(const QModelIndex& index) const;

private:
    std::unique_ptr<TreeItem> root_;
};


class DocumentsModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT

public:
    enum DocumentRole {
        TitleRole = Qt::DisplayRole,
        FirstSentenceRole = Qt::UserRole,
        PathRole
    };
    Q_ENUM(DocumentRole)

    DocumentsModel(QObject* parent = nullptr);
    QVariant data(const QModelIndex& index, const int role = Qt::DisplayRole) const;

    QHash<int, QByteArray> roleNames() const { return roles_; }
    int rowCount(const QModelIndex& = QModelIndex()) const { return documents_.count(); }

    Q_INVOKABLE QVariantMap get(const int row) const { return documents_.value(row).GetData(); }

    Q_INVOKABLE void remove(const int row);
    Q_INVOKABLE void append(const QString& title, const QString& first_sentence, const QString& path);
    Q_INVOKABLE void set(const int row, const QString& title, const QString& first_sentence, const QString& path);

private:
    const QHash<int, QByteArray> roles_ {
        {TitleRole, "title"},
        {FirstSentenceRole, "first_sentence"},
        {PathRole, "path"}
    };

    struct Document {
        QVariantMap GetData()
        {
            return {{"title", title},
                    {"first_sentence", first_sentence},
                    {"path", path}
            };
        }

        QString title;
        QString first_sentence;
        QString path;

        //here should be the list of abstract blockss
    };

    QList<Document> documents_;
};

#endif // DOCUMENTSMODEL_H
