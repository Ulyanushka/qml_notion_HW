#ifndef DOCUMENTSMODEL_H
#define DOCUMENTSMODEL_H

#include <QAbstractListModel>
#include <QQmlEngine>
#include <QVariant>


class Block : QObject
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

    Q_INVOKABLE BlockType GetType() const { return type_; }
    Q_INVOKABLE QVariant GetContent() const { return content_; }

private:
    BlockType type_;
    QVariant content_;
};


class NotionDocument : QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    NotionDocument(const QString& title, const QString& file_path);

    Q_INVOKABLE QString GetTitle() const { return title_; }
    Q_INVOKABLE QList<Block> GetBlocks() const { return blocks_; }

private:
    void SetBlocks();

    QString title_;
    QString file_path_;
    QList<Block> blocks_;
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
