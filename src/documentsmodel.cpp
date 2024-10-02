#include "documentsmodel.h"


const QList<QStringList> documents_start_data {
    {"Память, мозг, речь. Как мы понимаем местоимения?",
     "Когда речь заходит про общение и память, то наука в целом объясняет природу абстрактных образов, которыми мы обмениваемся друг с другом.",
     "https://habr.com/ru/articles/847480/"
    },
    {"Шаблоны проектирования для баз данных",
     "Существуют различные шаблоны проектирования облачных сервисов.",
     "https://habr.com/ru/companies/otus/articles/843940/"
    },
    {"От автоматонов до драконов: 9 ожидаемых игр осени 2024",
     "В прошлом году выпустили рекордное количество успешных игр для ПК и консолей.",
     "https://habr.com/ru/companies/skillfactory/articles/847452/"
    }
};


DocumentsModel::DocumentsModel(QObject* parent ) : QAbstractListModel(parent)
{
    for (const auto& doc : documents_start_data) {
        documents_.append({doc[TitleRole], doc[FirstSentenceRole], doc[PathRole]});
    }
}

QVariant DocumentsModel::data(const QModelIndex& index, const int role) const
{
    if (index.row() < rowCount()) {
        switch (role) {
            case TitleRole:         return documents_.at(index.row()).title;
            case FirstSentenceRole: return documents_.at(index.row()).first_sentence;
            case PathRole:          return documents_.at(index.row()).path;
            default:                return QVariant();
        }
    }
    return QVariant();
}

void DocumentsModel::remove(const int row)
{
    if (row < 0 || row >= documents_.count()) {
        return;
    }

    beginRemoveRows(QModelIndex(), row, row);
    documents_.removeAt(row);
    endRemoveRows();
}

void DocumentsModel::append(const QString& title, const QString& first_sentence, const QString& path)
{
    int row = 0;
    while (row < documents_.count()
           && title > documents_.at(row).title) {
        ++row;
    }
    beginInsertRows(QModelIndex(), row, row);
    documents_.insert(row, {title, first_sentence, path});
    endInsertRows();
}

void DocumentsModel::set(const int row, const QString& title, const QString& first_sentence, const QString& path)
{
    if (row < 0 || row >= documents_.count()) {
        return;
    }

    documents_.replace(row, {title, first_sentence, path});
    emit dataChanged(index(row, 0), index(row, 0), { TitleRole, FirstSentenceRole, PathRole});
}
