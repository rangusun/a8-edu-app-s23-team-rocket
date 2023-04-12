#include "lab10.h"
#include "ui_lab10.h"
#include <QPainter>
#include <QPen>

Lab10::Lab10(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Lab10)
{
    ui->setupUi(this);

    // populate the combo box
        ui->shapeComboBox->addItem("Rectangle");
        ui->shapeComboBox->addItem("Ellipse");

    // put limits on the pen width
       ui->penWidthSpinBox->setRange(0, 20);

       // make a connection to changes in the values to redraw
       connect(ui->shapeComboBox,
               &QComboBox::activated,
               this,
               &Lab10::valuesChanged);
       connect(ui->penWidthSpinBox,
               &QSpinBox::valueChanged,
               this,
               &Lab10::valuesChanged);
}

Lab10::~Lab10()
{
    delete ui;
}

void Lab10::valuesChanged()
{
    update();
}

// Override the default paintEvent with drawing of the shape
void Lab10::paintEvent(QPaintEvent *)
{
    // Create a painter
     QPainter painter(this);
     QPen pen(Qt::black);
     int penWidth = ui->penWidthSpinBox->value();
     pen.setWidth(penWidth);
     painter.setPen(pen);
     painter.setBrush(Qt::blue);


     QRect rect(10, 20, 80, 60);
     int shapeNum = ui->shapeComboBox->currentIndex();
     switch (shapeNum) {
     case 0:
     painter.drawRect(rect);
     break;
     case 1:
     painter.drawEllipse(rect);
     break;
     }
}

