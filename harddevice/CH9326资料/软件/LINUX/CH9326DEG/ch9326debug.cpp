#include "ch9326debug.h"
#include "ui_ch9326dlg.h"
#include "ch9326dll/ch9326.h"
#include <QSettings>
#include <QMessageBox>
#include <QDebug>

#include <iostream>
using namespace std;
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <unistd.h>

bool ENABLETHREAD = false;
unsigned char index_app;
long long m_rcvTotalSize;
bool OutputState = false;
char m_previousChar;

CH9326DEBUG::CH9326DEBUG(QWidget *parent) :
    QWidget(parent),
    m_sndTotalSize(0),
    m_wIODir(0),
    m_wIOData(0),
    m_isConnected(false)
{
    this->setupUi(this);
    initDialog();
    m_hexOutputCb->setEnabled(true);
    m_rcvStopBtn->setEnabled(false);
    m_setConfig->setEnabled(false);
    m_recvArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_sendArea->setFocus();
    index_app = -1;
    m_rcvTotalSize = 0;
    m_previousChar = '\0';
    thread = new MyThread;
    connect(thread, SIGNAL(emitsignal(QString)), this, SLOT(addOutput(QString)));

    connect(m_openDevice, SIGNAL(clicked()), this, SLOT(openDevice()));
    connect(m_setConfig, SIGNAL(clicked()), this, SLOT(setConfig()));
    connect(m_sendBtn, SIGNAL(clicked()), this, SLOT(sendData()));
    connect(m_rcvBtn, SIGNAL(clicked()), this, SLOT(startReceiveData()));
    connect(m_rcvStopBtn, SIGNAL(clicked()), this, SLOT(stopRcvData()));
    connect(m_rcvClearBtn, SIGNAL(clicked()), this, SLOT(clearRcvArea()));
    connect(m_hexInputCb, SIGNAL(clicked()), this, SLOT(outputStateChange()));

    connect(m_outputBtn, SIGNAL(clicked()), this, SLOT(setGpioData()));
    connect(m_inputBtn, SIGNAL(clicked()), this, SLOT(getGpio()));
    connect(m_setIoDirBtn, SIGNAL(clicked()), this, SLOT(setGpioDir()));

}

void CH9326DEBUG::initDialog()
{
    m_openDevice->setText("Search");
    OnCheckRadioState();
    readSettings();
    setRadioSignalConnection();
}

void CH9326DEBUG::outputStateChange()
{
    if(m_hexInputCb->isChecked()) {
        OutputState = true;
    } else {
        OutputState = false;
    }
}

void CH9326DEBUG::setRadioSignalConnection()
{
    /* IO1 */
    connect(m_inBtn1, SIGNAL(clicked()), this, SLOT(OnRadioIo1Input()));
    connect(m_outBtn1, SIGNAL(clicked()), this, SLOT(OnRadioIo1Output()));
    connect(m_highBtn1, SIGNAL(clicked()), this, SLOT(OnRadioIo1High()));
    connect(m_lowBtn1, SIGNAL(clicked()), this, SLOT(OnRadioIo1Low()));
    /* IO2 */
    connect(m_inBtn2, SIGNAL(clicked()), this, SLOT(OnRadioIo2Input()));
    connect(m_outBtn2, SIGNAL(clicked()), this, SLOT(OnRadioIo2Output()));
    connect(m_highBtn2, SIGNAL(clicked()), this, SLOT(OnRadioIo2High()));
    connect(m_lowBtn2, SIGNAL(clicked()), this, SLOT(OnRadioIo2Low()));
    /* IO3 */
    connect(m_inBtn3, SIGNAL(clicked()), this, SLOT(OnRadioIo3Input()));
    connect(m_outBtn3, SIGNAL(clicked()), this, SLOT(OnRadioIo3Output()));
    connect(m_highBtn3, SIGNAL(clicked()), this, SLOT(OnRadioIo3High()));
    connect(m_lowBtn3, SIGNAL(clicked()), this, SLOT(OnRadioIo3Low()));
    /* IO4 */
    connect(m_inBtn4, SIGNAL(clicked()), this, SLOT(OnRadioIo4Input()));
    connect(m_outBtn4, SIGNAL(clicked()), this, SLOT(OnRadioIo4Output()));
    connect(m_highBtn4, SIGNAL(clicked()), this, SLOT(OnRadioIo4High()));
    connect(m_lowBtn4, SIGNAL(clicked()), this, SLOT(OnRadioIo4Low()));
}

void CH9326DEBUG::OnCheckRadioState()
{
    if(m_wIODir & 0x01) {
        m_highBtn1->setEnabled(true);
        m_lowBtn1->setEnabled(true);
    } else {
        m_highBtn1->setEnabled(false);
        m_lowBtn1->setEnabled(false);
    }
    if(m_wIODir & 0x02) {
        m_highBtn2->setEnabled(true);
        m_lowBtn2->setEnabled(true);
    } else {
        m_highBtn2->setEnabled(false);
        m_lowBtn2->setEnabled(false);
    }
    if(m_wIODir & 0x04) {
        m_highBtn3->setEnabled(true);
        m_lowBtn3->setEnabled(true);
    } else {
        m_highBtn3->setEnabled(false);
        m_lowBtn3->setEnabled(false);
    }
    if(m_wIODir & 0x08) {
        m_highBtn4->setEnabled(true);
        m_lowBtn4->setEnabled(true);
    } else {
        m_highBtn4->setEnabled(false);
        m_lowBtn4->setEnabled(false);
    }

    if(m_wIOData & 0x01) {
        m_highBtn1->setChecked(true);
    } else {
        m_lowBtn1->setChecked(true);
    }
    if(m_wIOData & 0x02) {
        m_highBtn2->setChecked(true);
    } else {
        m_lowBtn2->setChecked(true);
    }
    if(m_wIOData & 0x04) {
        m_highBtn3->setChecked(true);
    } else {
        m_lowBtn3->setChecked(true);
    }
    if(m_wIOData & 0x08) {
        m_highBtn4->setChecked(true);
    } else {
        m_lowBtn4->setChecked(true);
    }
}

void CH9326DEBUG::saveSettings()
{
    QSettings settings;
    settings.setValue("/ch9326/baudrate", m_baudCb->currentItem());
    settings.setValue("/ch9326/databits", m_dataBitsCb->currentItem());
    settings.setValue("/ch9326/stopbits", m_stopBitsCb->currentItem());
    settings.setValue("/ch9326/parity", m_parityCb->currentItem());
}

void CH9326DEBUG::readSettings()
{
    QSettings settings;
    m_baudCb->setCurrentIndex(settings.value("/ch9326/baudrate", 12).toInt());
    m_dataBitsCb->setCurrentIndex(settings.value("/ch9326/databits", 3).toInt());
    m_stopBitsCb->setCurrentIndex(settings.value("/ch9326/stopbits", 0).toInt());
    m_parityCb->setCurrentIndex(settings.value("/ch9326/parity", 0).toInt());
}

/*
 * Open Device
 */
void CH9326DEBUG::openDevice()
{
    if(m_openDevice->text() == "Search") {
        int m_num = ch9326_find();
        if(!m_num) {
            QString mStr = "Not Found device.<br>Please Insert CH9326 Device";
            showMsgError(mStr);
            return;
        } else {
            m_openDevice->setText("OpenDev");
            m_deviceInfo->setText(tr("VID:1A86,PID:E010/DeviceNum:%1").arg(m_num));
            for(int i = 0; i < m_num; i++) {
                m_deviceName->insertItem(tr("CH9326 Device : %1").arg(i + 1), i);
            }
            m_deviceName->setCurrentItem(0);
        }
    } else if(m_openDevice->text() == "OpenDev") {
        index_app = m_deviceName->currentIndex();
        if(!ch9326_open(index_app)) {
            QString mStr = "Open device failed.";
            showMsgError(mStr);
            return;
        } else {
            m_isConnected = true;
            m_setConfig->setEnabled(true);
        }
        m_openDevice->setText("CloseDev");
    } else if(m_openDevice->text() == "CloseDev") {
        if(m_isConnected) {
            ch9326_close(index_app);
            m_isConnected = false;
        }
//            stopRcvData();
        ENABLETHREAD = false;
        m_rcvBtn->setEnabled(true);
        m_rcvStopBtn->setEnabled(false);
        if(thread->isRunning()) {
            thread->quit();
        }
            int itemNum =  m_deviceName->count();
            for(int j = 0; j < itemNum; j++) {
                m_deviceName->removeItem(j);
            }
            m_deviceName->clear();
            m_deviceInfo->setText(tr(""));
            m_openDevice->setText("Search");
            m_edit->setText("0");
            m_rcvTotalSize = 0;
    }

}

void string_to_char(const unsigned char *str, unsigned char *dst)
{
    int strlength = (int)strlen((char *)str);
    unsigned char temp[SERIALCOM_BUFSIZE];
    int i, j = 0;
    memset(temp, 0, sizeof(unsigned char) * SERIALCOM_BUFSIZE);
    for(i = 0; i < strlength; i++)
    {
        if(*(str + i) >= '0' && *(str + i) <= '9')
        {
            temp[i] = *(str + i) -'0';
        }
        else if(*(str + i) >= 'a' && *(str + i) <= 'f')
        {
            temp[i] = *(str + i) -'a' + 10;
        }
        else if(*(str + i) >= 'A' && *(str + i) <= 'F')
        {
            temp[i] = *(str + i) -'A' + 10;
        }
    }
    for(i= 0; i < strlength; i++)
    {
        dst[j++] = temp[i] * 16 + temp[++i];
    }
    return;
}

/*
 * Send Data
 */
void CH9326DEBUG::sendData()
{
    int mLen;
    QString cmd=m_sendArea->text().trimmed();
    if(cmd != NULL)
    {
            if(m_hexOutputCb->isChecked()) {
                int mNum = cmd.length();
                if(mNum % 2 != 0) {
                    cmd.append("0");
                }
                mNum = cmd.length() / 2;
                unsigned char bytes[mNum];
                unsigned char *oBuffer = (unsigned char *)cmd.toLatin1().data();
                string_to_char(oBuffer, bytes);
                mLen = ch9326_send(index_app, bytes, mNum);
            } else {
                unsigned char *bytes = (unsigned char *)cmd.toLatin1().data();
                int length = cmd.length();
                mLen = ch9326_send(index_app, bytes, length);
            }
    }
}

/*
 *  Set Config
 */
void CH9326DEBUG::setConfig()
{
    int rate = 0;
    int check = 0;
    int stop_bits = 0;
    int data_bits = 0;
    int baudrate = m_baudCb->currentText().toInt();
    int dataBits = m_dataBitsCb->currentText().toInt();
    QString parity = m_parityCb->currentText();
    int stop = m_stopBitsCb->currentText().toInt();

    switch(baudrate) {
    case 300:
        rate = 0x01;
        break;
    case 600:
        rate = 0x02;
        break;
    case 1200:
        rate = 0x03;
        break;
    case 2400:
        rate = 0x04;
        break;
    case 4800:
        rate = 0x05;
        break;
    case 9600:
        rate = 0x06;
        break;
    case 14400:
        rate = 0x07;
        break;
    case 19200:
        rate = 0x08;
        break;
    case  28800:
        rate = 0x09;
        break;
    case 38400:
        rate = 0x0a;
        break;
    case 57600:
        rate = 0x0b;
        break;
    case 76800:
        rate = 0x0c;
        break;
    case 115200:
    default:
        rate = 0x0d;
        break;
    }

    switch (dataBits) {
    case 5:
        data_bits = 0x01;
        break;
    case 6:
        data_bits = 0x02;
        break;
    case 7:
        data_bits = 0x03;
        break;
    case 8:
    default:
        data_bits = 0x04;
        break;
    }

    if(parity == "Odd") {
        check = 0x01;
    } else if(parity == "Even") {
        check = 0x02;
    } else if(parity == "Space") {
        check = 0x03;
    } else {
        check = 0x04;
    }

    switch(stop) {
    case 1:
        stop_bits = 0x01;
        break;
    case 2:
        stop_bits = 0x02;
        break;
    default:
        stop_bits = 0x01;
        break;
    }

    bool flag = ch9326_set(index_app, rate, check, stop_bits, data_bits, 0x10);
    if(!flag) {
        QString mStr = "Set UART Configuration Error";
        showMsgError(mStr);
    }

}

/*
 * Start Receive Data
 */
void CH9326DEBUG::startReceiveData()
{
    ENABLETHREAD = true;
    m_rcvBtn->setEnabled(false);
    m_rcvStopBtn->setEnabled(true);
    thread->start();
}

void CH9326DEBUG::addOutput(const QString& mStr)
{
    if (mStr.isEmpty())
    {
       return;
    }
    m_outputBuffer = m_recvArea->text();
    if(m_outputBuffer.length() > 1000) {
        m_outputBuffer.clear();
    }
    m_outputBuffer.append(mStr);
    m_recvArea->clear();
    m_recvArea->append(m_outputBuffer);
    m_outputBuffer.clear();
    m_edit->setText(tr("%1").arg(m_rcvTotalSize));
}

/*
 * Stop CH9326 Receive
 */
void CH9326DEBUG::stopRcvData()
{
    ENABLETHREAD = false;
    m_rcvBtn->setEnabled(true);
    m_rcvStopBtn->setEnabled(false);
    thread->quit();
}

/*
 *  Clear receive area
 */
void CH9326DEBUG::clearRcvArea()
{
        m_edit->setText("0");
        m_rcvTotalSize = 0;
        m_recvArea->clear();
}

/*
 * SET GPIO DATA
 */
void CH9326DEBUG::setGpioData()
{
    int flag;
    QString mStr;
    if(!ch9326_connected(index_app)) {
        mStr = "Device Not Connected";
        showMsgError(mStr);
        return;
    }
    flag = ch9326_set_gpiodata(index_app, m_wIOData);
    if(!flag) {
        mStr = "Set GPIO Signal Level Error";
        showMsgError(mStr);                     // Error
        return;
    }
}

/*
 * SET GPIO DIR
 */
void CH9326DEBUG::setGpioDir()
{
    int flag;
    QString mStr;
    if(!ch9326_connected(index_app)) {
        mStr = "Device Not Connected";
        showMsgError(mStr);
        return;
    }
    flag = ch9326_set_gpiodir(index_app, m_wIODir);
    if(!flag) {
        mStr = "Set GPIO Director Error";
        showMsgError(mStr);
        return;
    }
}

/*
 * Get GPIO
 */
void CH9326DEBUG::getGpio()
{
    int flag;
    char data;
    QString mStr;
    if(!ch9326_connected(index_app)) {
        mStr = "Device not connected";
        showMsgError(mStr);
        return;
    }
    flag = ch9326_get_gpio(index_app, &data);
    if(!flag) {
         mStr = "Read IO Error";
         showMsgError(mStr);
         return;
    } else {
        m_wIOData = data & 0x0F;
        OnCheckRadioState();
    }
}

void CH9326DEBUG::showMsgError(const QString &string)
{
    QMessageBox::critical(this, tr("Operator Error"), string, QMessageBox::Ok);
}

/*
 *  IO1
 */
void CH9326DEBUG::OnRadioIo1Input()
{
    m_wIODir &= 0xFE;
    OnCheckRadioState();
}

void CH9326DEBUG::OnRadioIo1Output()
{
    m_wIODir |= 0x01;
    OnCheckRadioState();
}

void CH9326DEBUG::OnRadioIo1High()
{
    m_wIOData |= 0x01;
    OnCheckRadioState();
}

void CH9326DEBUG::OnRadioIo1Low()
{
    m_wIOData &= 0xFE;
    OnCheckRadioState();
}

/*
 *  IO2
 */
void CH9326DEBUG::OnRadioIo2Input()
{
    m_wIODir &= 0xFD;
    OnCheckRadioState();
}

void CH9326DEBUG::OnRadioIo2Output()
{
    m_wIODir |= 0x02;
    OnCheckRadioState();
}

void CH9326DEBUG::OnRadioIo2High()
{
    m_wIOData |= 0x02;
    OnCheckRadioState();
}

void CH9326DEBUG::OnRadioIo2Low()
{
    m_wIOData &= 0xFD;
    OnCheckRadioState();
}

/*
 *  IO3
 */
void CH9326DEBUG::OnRadioIo3Input()
{
    m_wIODir &= 0xFB;
    OnCheckRadioState();
}

void CH9326DEBUG::OnRadioIo3Output()
{
    m_wIODir |= 0x04;
    OnCheckRadioState();
}

void CH9326DEBUG::OnRadioIo3High()
{
    m_wIOData |= 0x04;
    OnCheckRadioState();
}

void CH9326DEBUG::OnRadioIo3Low()
{
    m_wIOData &= 0xFB;
    OnCheckRadioState();
}

/*
 *  IO4
 */
void CH9326DEBUG::OnRadioIo4Input()
{
    m_wIODir &= 0xF7;
    OnCheckRadioState();
}

void CH9326DEBUG::OnRadioIo4Output()
{
    m_wIODir |= 0x08;
    OnCheckRadioState();
}

void CH9326DEBUG::OnRadioIo4High()
{
    m_wIOData |= 0x08;
    OnCheckRadioState();
}

void CH9326DEBUG::OnRadioIo4Low()
{
    m_wIOData &= 0xF7;
    OnCheckRadioState();
}

CH9326DEBUG::~CH9326DEBUG()
{
    if(thread->isRunning()) {
        thread->exit(0);
    }
    if(m_isConnected) {
        ch9326_close(index_app);
        m_isConnected = false;
    }
    m_outputBuffer.clear();
}

void MyThread::run()
{
    char buffer[MAXPACKETSIZE];
    int mLen = 0;
    QString text;
    while(ENABLETHREAD) {
        mLen = ch9326_recv(index_app, buffer, MAXPACKETSIZE);
        if(mLen > 0) {
            m_rcvTotalSize += mLen;
           const char* c = buffer;
           char buf[16];
           for (int i = 0; i < mLen; i++)
           {
              if (OutputState)
              {
                 unsigned int b=*c;
                 snprintf(buf, 16, "%02x ", b & 0xff);
                 text += buf;
              }
              else
              {
                 // also print a newline for \r, and print only one newline for \r\n
                 if ((isprint(*c)) || (*c == '\n') || (*c == '\r'))
                 {
                    if (*c == '\r')
                    {
                       text += '\n';
                    }
                    else if (*c == '\n')
                    {
                       if (m_previousChar != '\r')
                       {
                          text += '\n';
                       }
                    }
                    else
                    {
                       text += (*c);
                    }
                    m_previousChar = *c;
                 }
                 else
                 {
                    unsigned int b = *c;
                    snprintf(buf, 16, "\ 0x%02x", b & 0xff);
                    text += buf;
                 }
              }
              c++;
           }
           emit emitsignal(text);
           text.clear();
        }
        if(!ENABLETHREAD) {
            break;
        }
    }
}
