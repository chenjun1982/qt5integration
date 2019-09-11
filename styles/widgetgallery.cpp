/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtWidgets>

#include "norwegianwoodstyle.h"
#include "widgetgallery.h"

//! [0]
WidgetGallery::WidgetGallery(QWidget *parent)
    : QMainWindow(parent)
{
    originalPalette = QApplication::palette();

    styleComboBox = new QComboBox;
    styleComboBox->addItem("NorwegianWood");
    styleComboBox->addItems(QStyleFactory::keys());
    styleComboBox->setToolTip("Hello");

    styleLabel = new QLabel(tr("&Style:"));
    styleLabel->setBuddy(styleComboBox);

    useStylePaletteCheckBox = new QCheckBox(tr("&Use style's standard palette"));
    useStylePaletteCheckBox->setChecked(false);

    disableWidgetsCheckBox = new QCheckBox(tr("&Disable widgets"));

    changeStyle("chameleon");

    createTopLeftGroupBox();
    createTopRightGroupBox();
    createBottomLeftTabWidget();
    createBottomRightGroupBox();
    createProgressBar();
//! [0]

//! [1]
    connect(styleComboBox, SIGNAL(activated(QString)),
//! [1] //! [2]
            this, SLOT(changeStyle(QString)));
    connect(useStylePaletteCheckBox, SIGNAL(toggled(bool)),
            this, SLOT(changePalette()));
    connect(disableWidgetsCheckBox, SIGNAL(toggled(bool)),
            topLeftGroupBox, SLOT(setDisabled(bool)));
    connect(disableWidgetsCheckBox, SIGNAL(toggled(bool)),
            topRightGroupBox, SLOT(setDisabled(bool)));
    connect(disableWidgetsCheckBox, SIGNAL(toggled(bool)),
            bottomLeftTabWidget, SLOT(setDisabled(bool)));
    connect(disableWidgetsCheckBox, SIGNAL(toggled(bool)),
            bottomRightGroupBox, SLOT(setDisabled(bool)));
//! [2]

//! [3]
    QWidget *mainWidget = new QWidget();
    QHBoxLayout *topLayout = new QHBoxLayout;
//! [3] //! [4]
    topLayout->addWidget(styleLabel);
    topLayout->addWidget(styleComboBox);
    topLayout->addStretch(1);
    topLayout->addWidget(useStylePaletteCheckBox);
    topLayout->addWidget(disableWidgetsCheckBox);

    QGridLayout *mainLayout = new QGridLayout(mainWidget);
    mainLayout->addLayout(topLayout, 0, 0, 1, 2);
    mainLayout->addWidget(topLeftGroupBox, 1, 0);
    mainLayout->addWidget(topRightGroupBox, 1, 1);
    mainLayout->addWidget(bottomLeftTabWidget, 2, 0);
    mainLayout->addWidget(bottomRightGroupBox, 2, 1);
    mainLayout->addWidget(progressBar, 3, 0, 1, 2);
    mainLayout->setRowStretch(1, 1);
    mainLayout->setRowStretch(2, 1);
    mainLayout->setColumnStretch(0, 1);
    mainLayout->setColumnStretch(1, 1);

    setWindowTitle(tr("Styles"));

    setCentralWidget(mainWidget);

    QMenu *firstLayer = new QMenu("first");
    menuBar()->addAction("chameleon")->setMenu(firstLayer);
    firstLayer->addAction("menu 1")->setIcon(QIcon::fromTheme("document-open"));
    firstLayer->addAction("menu 2")->setEnabled(false);
    firstLayer->addSection("Section");
    firstLayer->addAction("menu 3")->setCheckable(true);
    firstLayer->addSeparator();

    QMenu *secondLayer = new QMenu("second");
    firstLayer->addMenu(secondLayer);
    QActionGroup *group = new QActionGroup(this);
    group->setExclusive(true);
    QAction *sa1 = new QAction("submenu 1");
    sa1->setCheckable(true);
    group->addAction(sa1);
    QAction *sa2 = new QAction("submenu 2");
    sa2->setCheckable(true);
    sa2->setIcon(QIcon::fromTheme("application-exit"));
    group->addAction(sa2);
    QAction *sa3 = new QAction("submenu 3");
    sa3->setCheckable(true);
    sa3->setShortcut(QKeySequence::New);
    group->addAction(sa3);
    secondLayer->addActions(group->actions());
    secondLayer->setLayoutDirection(Qt::RightToLeft);

    menuBar()->addAction("dlight");
    menuBar()->addAction("ddark");
    menuBar()->addAction("dsemidark");
    menuBar()->addAction("dsemilight");

    connect(menuBar(), &QMenuBar::triggered, this, [this](const QAction * action) {
        changeStyle(action->text());
    });
}
//! [4]

//! [5]
void WidgetGallery::changeStyle(const QString &styleName)
//! [5] //! [6]
{
    if (styleName == "NorwegianWood") {
        QApplication::setStyle(new NorwegianWoodStyle);
    } else {
        QApplication::setStyle(QStyleFactory::create(styleName));
    }
    changePalette();
}
//! [6]

//! [7]
void WidgetGallery::changePalette()
//! [7] //! [8]
{
    if (useStylePaletteCheckBox->isChecked()) {
        QApplication::setPalette(QApplication::style()->standardPalette());
     } else {
//        QApplication::setPalette(originalPalette);
        QApplication::setAttribute(Qt::AA_SetPalette, false);
    }
}
//! [8]

//! [9]
void WidgetGallery::advanceProgressBar()
//! [9] //! [10]
{
    int curVal = progressBar->value();
    int maxVal = progressBar->maximum();
    progressBar->setValue(curVal + (maxVal - curVal) / 100);
}
//! [10]

//! [11]
void WidgetGallery::createTopLeftGroupBox()
//! [11] //! [12]
{
    topLeftGroupBox = new QGroupBox(tr("Group 1"));

    radioButton1 = new QRadioButton(tr("Radio button 1"));
    radioButton2 = new QRadioButton(tr("Radio button 2"));
    radioButton3 = new QRadioButton(tr("Radio button 3"));
    radioButton1->setChecked(true);

    checkBox = new QCheckBox(tr("Tri-state check box"));
    checkBox->setTristate(true);
    checkBox->setCheckState(Qt::PartiallyChecked);

    connect(radioButton1, &QRadioButton::clicked, this, [&] {
        bottomLeftTabWidget->setDocumentMode(!bottomLeftTabWidget->documentMode());
    });
    connect(radioButton2, &QRadioButton::clicked, this, [&] {
        bottomLeftTabWidget->setTabShape(QTabWidget::Rounded);
        bottomLeftTabWidget->update();
    });
    connect(radioButton3, &QRadioButton::clicked, this, [&] {
        bottomLeftTabWidget->setTabShape(QTabWidget::Triangular);
        bottomLeftTabWidget->update();
    });

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(radioButton1);
    layout->addWidget(radioButton2);
    layout->addWidget(radioButton3);
    layout->addWidget(checkBox);
    layout->addStretch(1);
    topLeftGroupBox->setLayout(layout);
}
//! [12]

void WidgetGallery::createTopRightGroupBox()
{
    topRightGroupBox = new QGroupBox(tr("Group 2"));

    defaultPushButton = new QPushButton(tr("Default Push Button"));
    defaultPushButton->setDefault(true);

    togglePushButton = new QPushButton(tr("Toggle Push Button"));
    togglePushButton->setCheckable(true);
    togglePushButton->setChecked(true);

    flatPushButton = new QPushButton(tr("Flat Push Button"));
    flatPushButton->setFlat(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(defaultPushButton);
    layout->addWidget(togglePushButton);
    layout->addWidget(flatPushButton);
    layout->addStretch(1);
    topRightGroupBox->setLayout(layout);
}

void WidgetGallery::createBottomLeftTabWidget()
{
    bottomLeftTabWidget = new QTabWidget;
    bottomLeftTabWidget->setSizePolicy(QSizePolicy::Preferred,
                                       QSizePolicy::Ignored);

    bottomLeftTabWidget->setTabsClosable(true);
    bottomLeftTabWidget->setTabShape(QTabWidget::Triangular);

    QWidget *tab1 = new QWidget;
    tableWidget = new QTableWidget(10, 10);

    QHBoxLayout *tab1hbox = new QHBoxLayout;
    tab1hbox->setMargin(5);
    tab1hbox->addWidget(tableWidget);
    tab1->setLayout(tab1hbox);

    QWidget *tab2 = new QWidget;
    textEdit = new QTextEdit;

    textEdit->setPlainText(tr("Twinkle, twinkle, little star,\n"
                              "How I wonder what you are.\n"
                              "Up above the world so high,\n"
                              "Like a diamond in the sky.\n"
                              "Twinkle, twinkle, little star,\n"
                              "How I wonder what you are!\n"));

    QHBoxLayout *tab2hbox = new QHBoxLayout;
    tab2hbox->setMargin(5);
    tab2hbox->addWidget(textEdit);
    tab2->setLayout(tab2hbox);

    bottomLeftTabWidget->addTab(tab1, tr("&Table"));
    bottomLeftTabWidget->addTab(tab2, tr("Text &Edit"));
    bottomLeftTabWidget->addTab(new QWidget(), "tab 1");
    bottomLeftTabWidget->addTab(new QWidget(), "tab 2");
    bottomLeftTabWidget->addTab(new QWidget(), "tab 3");
    bottomLeftTabWidget->addTab(new QWidget(), "tab 4");
}

void WidgetGallery::createBottomRightGroupBox()
{
    bottomRightGroupBox = new QGroupBox(tr("Group 3"));
    bottomRightGroupBox->setCheckable(true);
    bottomRightGroupBox->setChecked(true);

    lineEdit = new QLineEdit("s3cRe7");
    lineEdit->setEchoMode(QLineEdit::Password);
    lineEdit->setClearButtonEnabled(true);

    spinBox = new QSpinBox(bottomRightGroupBox);
    spinBox->setValue(50);
    spinBox->setButtonSymbols(QAbstractSpinBox::PlusMinus);
    spinBox->setPrefix(" Prefix ");
    spinBox->setSuffix(" Suffix ");
    spinBox->setAlignment(Qt::AlignCenter);
    spinBox->setFrame(false);

    dateTimeEdit = new QDateTimeEdit(bottomRightGroupBox);
    dateTimeEdit->setDateTime(QDateTime::currentDateTime());

    comboBoxEdit = new QComboBox(bottomRightGroupBox);
    comboBoxEdit->addItem(QIcon::fromTheme("dde-file-manager"), "dde-file-manager");
    comboBoxEdit->addItem(QIcon::fromTheme("dde-introduction"), "dde-introduction");
    comboBoxEdit->addItem(QIcon::fromTheme("deepin-deb-installer"), "deepin-deb-installer");
    comboBoxEdit->setEditable(true);

    slider = new QSlider(Qt::Horizontal, bottomRightGroupBox);
    slider->setRange(0, 100);
    slider->setTickInterval(10);
    slider->setTickPosition(QSlider::TicksBelow);
    slider->setValue(40);

    scrollBar = new QScrollBar(Qt::Horizontal, bottomRightGroupBox);
    scrollBar->setValue(60);

    dial = new QDial(bottomRightGroupBox);
    dial->setValue(30);
    dial->setNotchesVisible(true);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(lineEdit, 0, 0, 1, 2);
    layout->addWidget(spinBox, 1, 0, 1, 2);
    layout->addWidget(dateTimeEdit, 2, 0, 1, 2);
    layout->addWidget(comboBoxEdit, 3, 0, 1, 2);
    layout->addWidget(slider, 4, 0);
    layout->addWidget(scrollBar, 5, 0);
    layout->addWidget(dial, 4, 1, 2, 1);
    layout->setRowStretch(6, 1);
    bottomRightGroupBox->setLayout(layout);
}

//! [13]
void WidgetGallery::createProgressBar()
{
    progressBar = new QProgressBar;
    progressBar->setRange(0, 10000);
    progressBar->setValue(0);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(advanceProgressBar()));
    timer->start(1000);
}
//! [13]
