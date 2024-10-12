#ifndef DOCUMENTSMODEL_H
#define DOCUMENTSMODEL_H

#include <QAbstractListModel>
#include <QQmlEngine>
#include <QVariant>


namespace BlockData
{
    Q_NAMESPACE
    enum Type {
        Document, //just a container for blocks
        JustAText, //for tests only I think
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
        HTML4Subset, //stansart tool
        None
    };
    Q_ENUM_NS(Type)
}


class TreeItem
{
public:
    explicit TreeItem(const QString& title, const BlockData::Type& type,
                      const QVariant& content = QVariant(), TreeItem* parent = nullptr)
        : block_(title, type, content), parent_(parent) {}

    TreeItem* parent() { return parent_; }
    TreeItem* child(int row) { return (row >= 0 && row < childCount()) ? children_.at(row).get() : nullptr; }

    void appendChild(std::unique_ptr<TreeItem>&& child) { children_.push_back(std::move(child)); }
    int childCount() const { return int(children_.size()); }
    int columnCount() const { return 1; }

    QString titleStr() const { return block_.title; }
    QList<QVariantMap> contentListMap() const;
    int row() const;

private:
    struct Block {
        Block(const QString& title, const BlockData::Type& type, const QVariant& content) {
            this->title = title;
            this->type = type;
            this->content = content;
        }
        QVariantMap GetContentMap() const {
            return{{"type", QVariant::fromValue(type)},
                   {"content", content}};
        }

        QString title;
        BlockData::Type type;
        QVariant content;
    };

    TreeItem* parent_;
    std::vector<std::unique_ptr<TreeItem>> children_;
    Block block_;
};


//TREE_MODEL=======================================================================================s

class DocumentsTreeModel : public QAbstractItemModel
{
    Q_OBJECT
    QML_ELEMENT

public:
    enum DocumentRole {
        TitleRole = Qt::DisplayRole,
        ContentRole = Qt::UserRole,
    };
    Q_ENUM(DocumentRole)

    Q_DISABLE_COPY_MOVE(DocumentsTreeModel)

    explicit DocumentsTreeModel(QObject* parent = nullptr);
    ~DocumentsTreeModel() override = default;

    Q_INVOKABLE QVariant headerData(int section, Qt::Orientation orientation, int role = TitleRole) const override;
    Q_INVOKABLE QVariant data(const QModelIndex& index, int role) const override;

    QHash<int, QByteArray> roleNames() const override { return roles_; }
    Qt::ItemFlags flags(const QModelIndex& index) const override;

    QModelIndex index(int row, int column, const QModelIndex& parent = {}) const override;
    QModelIndex parent(const QModelIndex& index) const override;

    int rowCount(const QModelIndex& parent = {}) const override;
    int columnCount(const QModelIndex& parent = {}) const override { return 1; }

private:
    void MakeTestModel();

    const QHash<int, QByteArray> roles_ {
        {TitleRole, "title"},
        {ContentRole, "content"}
    };

    std::unique_ptr<TreeItem> root_;
};


//LIST_MODEL=======================================================================================

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

    Q_INVOKABLE void remove(const int row);
    Q_INVOKABLE void append(const QString& title, const QString& first_sentence, const QString& path);
    Q_INVOKABLE void set(const int row, const QString& title, const QString& first_sentence, const QString& path);
    Q_INVOKABLE QVariantMap get(const int row) const { return documents_.value(row).GetData(); }

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
    };

    QList<Document> documents_;
};

#endif // DOCUMENTSMODEL_H
