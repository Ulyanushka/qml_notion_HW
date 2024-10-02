#ifndef DOCUMENTSMODEL_H
#define DOCUMENTSMODEL_H

#include <QAbstractListModel>
#include <QQmlEngine>


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
