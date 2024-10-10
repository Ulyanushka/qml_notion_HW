#include "documentsmodel.h"


Block* NotionDocument::GetBlock(const int id) const
{
    if (id < 0 || id >= blocks_.size()) {
        return nullptr;
    }
    return blocks_[id];
}

void NotionDocument::SetBlocks(const QString& file_path)
{
    //setting logic
}

//NEW_MODEL========================================================================================

int TreeItem::row() const
{
    if (parent_ == nullptr) {
        return 0;
    }
    const auto it = std::find_if(parent_->children_.cbegin(), parent_->children_.cend(),
                                 [this](const std::unique_ptr<TreeItem>& treeItem) {
                                     return treeItem.get() == this;
                                 });
    if (it != parent_->children_.cend()) {
        return std::distance(parent_->children_.cbegin(), it);
    }
    Q_ASSERT(false); // should not happen
    return -1;
}

DocumentsTreeModel::DocumentsTreeModel(const QList<NotionDocument*> documents, QObject* parent)
    : QAbstractItemModel(parent), root_(std::make_unique<TreeItem>("Title"))
{
    for(const auto& doc : documents) {
        auto doc_item = std::make_unique<TreeItem>(doc->GetTitle());
        for(const auto& block : doc->GetBlocks()) {
            doc_item->appendChild(std::make_unique<TreeItem>(block->GetTitle()));
        }
        root_->appendChild(std::move(doc_item));
    }
}

QVariant DocumentsTreeModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole) {
        return {};
    }

    auto item = static_cast<const TreeItem*>(index.internalPointer());
    return item->data();
}

Qt::ItemFlags DocumentsTreeModel::flags(const QModelIndex& index) const
{
    return (index.isValid()) ? QAbstractItemModel::flags(index)
                             : Qt::ItemFlags(Qt::NoItemFlags);
}

QVariant DocumentsTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return (orientation == Qt::Horizontal && role == Qt::DisplayRole) ? root_->data()
                                                                      : QVariant{};
}

QModelIndex DocumentsTreeModel::index(int row, int column, const QModelIndex& parent) const
{
    if (!hasIndex(row, column, parent)) {
        return {};
    }

    auto parentItem = (parent.isValid()) ? static_cast<TreeItem*>(parent.internalPointer())
                                         : root_.get();

    if (auto* childItem = parentItem->child(row)) {
        return createIndex(row, column, childItem);
    }
    return {};
}

QModelIndex DocumentsTreeModel::parent(const QModelIndex& index) const
{
    if (!index.isValid()) {
        return {};
    }

    auto childItem = static_cast<TreeItem*>(index.internalPointer());
    auto parentItem = childItem->parent();

    return (parentItem != root_.get()) ? createIndex(parentItem->row(), 0, parentItem)
                                       : QModelIndex{};
}

int DocumentsTreeModel::rowCount(const QModelIndex& parent) const
{
    if (parent.column() > 0) {
        return 0;
    }

    auto parentItem = (parent.isValid()) ? static_cast<const TreeItem*>(parent.internalPointer())
                                         : root_.get();

    return parentItem->childCount();
}

QStringList DocumentsTreeModel::GetPath(const QModelIndex& index) const
{
    if (!index.isValid()) {
        return {};
    }

    auto item = static_cast<TreeItem*>(index.internalPointer());
    return (item->parent() == root_.get()) ? QStringList({item->data()})
                                           : QStringList({item->parent()->data(), item->data()});
}

//OLD_MODEL========================================================================================

const QList<QStringList> documents_start_data {
    {"Память, мозг, речь. Как мы понимаем местоимения?",
     "Когда речь заходит про общение и память, то наука в целом объясняет природу абстрактных образов, которыми мы обмениваемся друг с другом.",
     "https://habr.com/ru/articles/847480/"},
    {"Шаблоны проектирования для баз данных",
     "Существуют различные шаблоны проектирования облачных сервисов.",
     "https://habr.com/ru/companies/otus/articles/843940/"},
    {"От автоматонов до драконов: 9 ожидаемых игр осени 2024",
     "В прошлом году выпустили рекордное количество успешных игр для ПК и консолей.",
     "https://habr.com/ru/companies/skillfactory/articles/847452/"},
    {"Бытие современного фуллстек-разработчика",
     "Я живу на периферии технологической тусовки.",
     "https://habr.com/ru/articles/457618/"},
    {"Лучшее резюме из тех, что я видел",
     "Позвольте мне рассказать историю о лучшем из виденных мною резюме облачного разработчика.",
     "https://habr.com/ru/companies/sportmaster_lab/articles/848408/"},
    {"Водные виды спорта как профилактика выгорания",
     "Меня зовут Александр Федюнин, я Product Lead команды интернет-магазина «Спортмастер» 3.0.",
     "https://habr.com/ru/companies/sportmaster_lab/articles/846524/"},
    {"Почему курсор мыши наклонён на 45°?",
     "Посетитель сайта вопросов-ответов StackExchange задал на первый взгляд глупый вопрос: а почему все курсоры во всех операционных системах немножко «кривые», то есть имеют определённый наклон, а не указывают прямо?",
     "https://habr.com/ru/articles/212939/"},
    {"Антарктика «зеленеет» с огромной скоростью",
     "Растительный покров на Антарктическом полуострове за последние четыре десятилетия увеличился более чем в десять раз, показало новое исследование.",
     "https://habr.com/ru/news/848254/"},
    {"Напоминание: лотерея гринкард 2026 уже началась",
     "С 2 октября и по 5 ноября продлится регистрация на розыгрыш гринкард 2026 года.",
     "https://habr.com/ru/news/848458/"},
    {"Google в тестовом режиме начал показывать в поиске галочку рядом с официальными ресурсами",
     "Google экспериментирует с новой функцией проверки в поиске, которая должна помочь пользователям избежать перехода по поддельным или мошенническим ссылкам на веб-сайты.",
     "https://habr.com/ru/news/848376/"}
};


DocumentsModel::DocumentsModel(QObject* parent) : QAbstractListModel(parent)
{
    for (const auto& doc : documents_start_data) {
        documents_.append({doc[0], doc[1], doc[2]});
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
