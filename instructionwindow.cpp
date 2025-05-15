#include "instructionwindow.h"
#include "ui_instructionwindow.h"
#include <QMessageBox>

InstructionWindow::InstructionWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InstructionWindow)
{
    try {
        ui->setupUi(this);
        setWindowTitle("Instructions");

        ui->instructionTextEdit->setReadOnly(true);
        ui->instructionTextEdit->setText(
            "Инструкция по использованию программы для анализа текстов:\n"
            "1. Основное окно (MainWindow)\n"
            "После запуска откроется главное окно с тремя кнопками:\n"
            "- 'Из консоли': Переход к вводу текста вручную.\n"
            "- 'Из фала': Переход к загрузке и анализу файла.\n"
            "- 'Инструкция': Открытие окна с инструкциями (это руководство).\n"
            "Нажмите одну из кнопок, чтобы начать работу. Главное окно скроется, и откроется соответствующее окно. Чтобы вернуться в главное окно, используйте кнопку 'Назад' в дочернем окне.\n"
            "2. Ввод текста (TextInputWindow)\n"
            "В поле ввода (inputTextEdit) введите текст для анализа\n"
            "Нажмите кнопку 'Анализировать'. Программа проверит, есть ли результаты в кэше. Если кэш доступен, результаты отобразятся сразу. Если нет, текст будет проанализирован.\n"
            "В поле resultTextEdit появятся статистики:\n"
            "- Total Words: Общее количество слов (с учётом повторений).\n"
            "- Unique Words: Количество уникальных слов.\n"
            "- Average Word Length: Средняя длина слова.\n"
            "- Most Frequent Word: Самое частое слово.\n"
            "- Word Frequencies: Список всех слов с их частотой.\n"
            "- График частотности отобразится в graphicsView (до 10 самых частых слов)\n"
            "Экспорт результатов:\n"
            "Нажмите 'Экспорт'.\n"
            "Выберите файл (.txt или .csv) через диалог сохранения.\n"
            "Для .txt: Экспортируются все статистики и частоты.\n"
            "Для .csv: Экспортируется таблица 'Word,Frequency' (например, для использования в Excel)\n"
            "Очистка кэша:\n"
            "Нажмите 'Очистить кеш', чтобы удалить сохранённые результаты. Появится сообщение 'Cache cleared'.\n"
            "Возврат:\n"
            "Нажмите 'Назад', чтобы вернуться в главное окно.\n"
            "3. Анализ файла (FileInputWindow)\n"
            "Выбор файла:\n"
            "Нажмите 'Анализировать'.В проводнике выберите файл .txt\n"
            "Анализ файла:\n"
            "Программа проверит кэш по пути файла. Если кэш доступен, результаты отобразятся сразу. Если нет, файл будет прочитан и проанализирован.\n"
            "Просмотр результатов:\n"
            "См. описание для TextInputWindow (поле resultTextEdit и график в graphicsView).\n"
            "Экспорт результатов:\n"
            "См. раздел 'Экспорт результатов' для TextInputWindow.\n"
            "Очистка кэша:\n"
            "См. раздел 'Очистка кэша' для TextInputWindow.\n"
            "Возврат:\n"
            "Нажмите 'Назад', чтобы вернуться в главное окно.\n"
            "Советы:\n"
            "Для TextInputWindow:\n"
            "Используйте колёсико мыши для масштабирования графика в graphicsView.\n"
            "Для FileInputWindow:\n"
            "Убедитесь, что файл не пустой и доступен для чтения.\n"
            "4. Инструкция (InstructionWindow)\n"
            "Нажмите 'Инструкция' в главном окне, чтобы открыть это окно.\n"
            "Прочитайте инструкции (данное руководство).\n"
            "Нажмите 'Назад', чтобы вернуться.\n"
            "5. Заключение\n"
            "Обратная связь или запросы на улучшения можно направить разработчику. Текущая версия протестирована на 16 мая 2025 года, время 01:43 AM EEST\n"
        );

        connect(ui->backButton, &QPushButton::clicked, this, &InstructionWindow::backToMainWindow);
    } catch (const std::exception& e) {
        showError(QString("Failed to initialize Instructions window: %1").arg(e.what()));
    }
}

InstructionWindow::~InstructionWindow()
{
    delete ui;
}

void InstructionWindow::backToMainWindow() {
    parentWidget()->show();
    close();
}

void InstructionWindow::showError(const QString& error) {
    QMessageBox::critical(this, "Error", error);
}
