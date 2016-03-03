#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow), clickCount(0)
{
    // I think this should always be first.
    ui->setupUi(this);

    // Disallow resizing of the window.
    ui->statusBar->setSizeGripEnabled(false);

    // Connect everything
    connectSignalsAndSlots();

    // Tell the model to start the game.
    gm.gameStart();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectSignalsAndSlots()
{
    // syntax for default slots is on_NAMEOFTHEWIDGET_NAMEOFTHESIGNAL
    // Manually connect the buttons to the methods:
    connect(ui->pushButton_start, SIGNAL(clicked(bool)), this, SLOT(pushButton_start_clicked()));
    connect(ui->pushButton_blue, SIGNAL(clicked(bool)), this, SLOT(pushButton_blue_clicked()));
    connect(ui->pushButton_red, SIGNAL(clicked(bool)), this, SLOT(pushButton_red_clicked()));

    // Signal that the state has changed.
    connect(&gm, SIGNAL(signalStateChange(int)), this, SLOT(state_changed(int)));

    // Signal for the progress bar to progress.
    connect(&gm, SIGNAL(signalProgressUpdate(int)), this, SLOT(updateProgressBar(int)));

    // Signal that the user has successfully completed the pattern.
    connect(&gm, SIGNAL(signalSequenceComplete()), &gm, SLOT(nextState()));
}

/**
 * @brief MainWindow::pushButton_start_clicked
 */
void MainWindow::pushButton_start_clicked()
{
    if (ui->pushButton_start->text() == "Reset")
    {
        QMessageBox msgBox;
        msgBox.setText("Are you sure you want to restart?");
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        int selection = msgBox.exec();

        if (selection == QMessageBox::Ok)
        {
            // Restart the game.
            gm.nextState(true);
            return;
        }
        else
        {
            return;
        }
    }
    gm.nextState();
}

/**
 * @brief MainWindow::pushButton_blue_clicked
 */
void MainWindow::pushButton_blue_clicked()
{
    gm.checkSequence("blue");
    ++clickCount;
    ui->progressBar->setValue(clickCount);
}

/**
 * @brief MainWindow::pushButton_red_clicked
 */
void MainWindow::pushButton_red_clicked()
{
    gm.checkSequence("red");
    ++clickCount;
    ui->progressBar->setValue(clickCount);
}

/**
 * @brief MainWindow::state_changed
 * @param nextState
 */
void MainWindow::state_changed(int nextState)
{
    // Start state
    if (nextState == game_model::gameState::Start)
    {
        ui->pushButton_start->setText("Start");
        ui->pushButton_blue->setDisabled(true);
        ui->pushButton_red->setDisabled(true);

        // http://stackoverflow.com/questions/14230265/what-is-the-proper-way-to-set-qprogressbar-to-update-from-the-logic-layer
        ui->progressBar->setRange(0, gm.getSequence().size());
        ui->progressBar->setValue(0);

        // Initialize the player label.
        ui->label_currentPlayer->setText(QString("Computer"));

        qDebug() << "Start!";
    }
    // Displaying state
    else if (nextState == game_model::gameState::DisplaySequence)
    {
        ui->pushButton_start->setText("Reset");
        ui->label_currentPlayer->setText(QString("Computer"));

//        for (auto const& value : gm.getSequence())
//        {
//            qDebug() << QString(value);
//        }
//        gm.nextState();

        // http://stackoverflow.com/questions/10492480/starting-qtimer-in-a-qthread
        // http://stackoverflow.com/questions/16501284/qt-updating-main-window-with-second-thread
        QThread* timer_thread = new QThread(this);
        QTimer* timer = new QTimer(0); // not 'this'!
        timer->setInterval(gm.getDisplaySequenceDelay());
        timer->moveToThread(timer_thread);
        connect(timer, SIGNAL(timeout()), this, SLOT(displayPattern()));
        // Make sure the timer gets started from timer_thread.
        QObject::connect(timer_thread, SIGNAL(started()), timer, SLOT(start()));
        timer_thread->start();
    }
    // User input state
    else if (nextState == game_model::gameState::UserInput)
    {
        ui->pushButton_blue->setEnabled(true);
        ui->pushButton_red->setEnabled(true);

        ui->label_currentPlayer->setText(QString("User"));
    }
    // User lost state.
    else if (nextState == game_model::gameState::GameOver)
    {
        QMessageBox message;
        message.setText(tr("Game Over!"));
        message.setInformativeText(
                    QString("Total number of rounds achieved: %1\nTotal number of moves: %2\n").arg(
                        gm.getTotalNumberOfRounds(), gm.getTotalMoves()));
        message.addButton(tr("Continue..."), QMessageBox::AcceptRole);
        message.exec();
    }
    // Error.
    else
    {
        QMessageBox message;
        message.setText(tr("Error!"));
        message.addButton(tr("Exit"), QMessageBox::AcceptRole);
        message.exec();
        QCoreApplication::exit();
    }
}

/**
 * @brief MainWindow::displayPattern
 */
void MainWindow::displayPattern()
{

}

/**
 * @brief MainWindow::updateProgressBar
 */
void MainWindow::updateProgressBar(int value)
{
    ui->progressBar->setValue(value);
}

/**
 * @brief MainWindow::pattern_complete
 */
void MainWindow::pattern_complete()
{

}
