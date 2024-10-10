#ifndef DOCUMENTSMODEL_H
#define DOCUMENTSMODEL_H

#include <QAbstractListModel>
#include <QQmlEngine>
#include <QVariant>

/*
class Block : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:

    Block(const QString& title, const QList<Block>& blocks,
          const BlockType& type = Block::Document, QObject* parent = nullptr)
        : QObject(parent), title_(title), type_(type), blocks_(blocks) {}

    Block(const QString& title, const QVariant& content,
          const BlockType& type = Block::None, QObject* parent = nullptr)
        : QObject(parent), title_(title), type_(type), content_(content) {}

    Q_INVOKABLE QString GetTitle() const { return title_; }
    Q_INVOKABLE QList<QVariantMap> GetData() const;

    BlockType GetType() const { return type_; }
    QVariant GetContent() const { return content_; }

private:
    QString title_;
    BlockType type_;
    QVariant content_ = QVariant(); //for block
    QList<Block> blocks_ = QList<Block>(); //for doc
};*/

/*
class NotionDocument : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    NotionDocument(const QString& title, const QString& file_path, QObject* parent = nullptr)
        : QObject(parent), title_(title), file_path_(file_path) {}

    NotionDocument(const QString& title, const QList<Block*> blocks, QObject* parent = nullptr)
        : QObject(parent), title_(title), blocks_(blocks) {}

    Q_INVOKABLE QString GetTitle() const { return title_; }
    Q_INVOKABLE QList<Block*> GetBlocks() const { return blocks_; }
    Q_INVOKABLE Block* GetBlock(const int id) const { return (id < 0 || id >= blocks_.size()) ? nullptr : blocks_[id]; }

private:
    QString title_;
    QString file_path_;
    QList<Block*> blocks_;
};
*/

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

    QString titleStr() const { return block_.title; }
    QList<QVariantMap> content() const;
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

    QVariant headerData(int section, Qt::Orientation orientation, int role = TitleRole) const override;
    Q_INVOKABLE QVariant data(const QModelIndex& index, int role) const override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    QModelIndex index(int row, int column, const QModelIndex& parent = {}) const override;
    QModelIndex parent(const QModelIndex& index) const override;

    int rowCount(const QModelIndex& parent = {}) const override;
    int columnCount(const QModelIndex& parent = {}) const override { return 1; }

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
    };

    QList<Document> documents_;
};

#endif // DOCUMENTSMODEL_H
