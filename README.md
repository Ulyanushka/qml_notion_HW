# qml_notion_HW

Что сделано:
1. Создана модель данных на снове QAbstractListModel, в которой содержатся документы в виде структуры из трёх qstring: title, first_sentence, path (пока здесь просто ссылка).

План:
1. Добавить список блоков в структуру документа.
2. Прописать DocsMenu, где будет выводиться список всех документов.
3. При тапе на документ из DocsMenu должнен открываться DocView, где можно просматривать документы.

--------------------------------------------------------------------------------------------------------------------

## Requirements
Приложение для чтения документов должно предоставлять иерархический рубрикатор документов для навигации между документами и область просмотра активного(выбранного) документа. Каждый элемент иерархии — отдельный документ являющийся текстовым файлом и состоящий из блоков, которые в свою очередь, отделены друга от друга переводом строки(\n). Блок может быть “отрисован” стандартными QtQuick или кастомным компонентами. Тип компонента для рендеринга может быть задан одним из свойств блока или определен автоматически, которые скрыты при просмотре, как теги, которые используются для поиска. Источником документов могут являться разные провайдеры, поэтому все они должны быть реализацией абстрактной модели данных и поддерживать отложенную загрузку(Lazy load), полнотекстовый поиск.

## Features
- Страница = Документ = Список блоков
- Типы блоков
    - Стандартный рендер QtQuick ([CommonMark](https://commonmark.org/help/) + [GitHub](https://guides.github.com/features/mastering-markdown/) extensions для tables и task)
        - Mesh
        - H1-заголовок
        - H2-заголовок
        - H3-заголовок
        - Italic
        - Bold
        - Underline
        - Link
        - Image
        - Bullet list
        - Numbered list
        - Horizontal line
        - Blockquote
        - Inline block (без поддержки каких-то конкретных языков)
        - Code block (без поддержки каких-то конкретных языков)
        - GitHub Tables
        - GitHub Tasks
    - Кастомный рендер
        - Теги документа (скрытый блок)
        - QtQuick MediaPlayer
        - HTML4 Subset (Стандартным [способом](https://doc.qt.io/qt-5/richtext-html-subset.html))
- Свойства блоков
    - Теги
    - Цвет левой кромки ([пример](https://docs.github.com/assets/cb-24696/mw-1440/images/help/writing/alerts-rendered.webp))
    - Badges(примечания) ([пример](https://docs.github.com/assets/cb-24696/mw-1440/images/help/writing/alerts-rendered.webp))
- Древовидный рубрикатор
- Поиск
    - Рубрикатору
    - Содержимому блоков
- Источники модели данных
    - file
