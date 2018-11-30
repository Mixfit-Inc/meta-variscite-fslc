// Author: Roberto Bellinato roberto.bellinato@egicon.com

#ifndef BYTEDATARAPPRESENTATION_H
#define BYTEDATARAPPRESENTATION_H

#include <QWidget>
#include <QCheckBox>
#include <QLabel>


namespace Ui {
class ByteDataRappresentation;
}

class ByteDataRappresentation : public QWidget
{
    Q_OBJECT

public:
    explicit ByteDataRappresentation(int index, bool readOnly=false, QWidget *parent = 0);
    ~ByteDataRappresentation();

    unsigned char getValue();
public slots:
    void CheckBoxUpdateFromInt(int val);
    void SpinBoxIntUpdateFromCheckbox();
    void setValue(int value);
private:
    Ui::ByteDataRappresentation *ui;
    QList<QCheckBox *> checkBoxList;
    QList<QLabel *> labelList;
    bool _readOnly;
};

#endif // BYTEDATARAPPRESENTATION_H
