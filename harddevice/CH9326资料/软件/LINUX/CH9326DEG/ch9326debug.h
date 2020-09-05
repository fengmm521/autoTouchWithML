#ifndef CH9326DEBUG_H
#define CH9326DEBUG_H

#include "ui_ch9326dlg.h"
#include <qtimer.h>
#include <QTime>
#include <QWidget>
#include <QThread>

#define SERIALCOM_BUFSIZE (4096)
#define MAXPACKETSIZE         (32)

class MyThread: public QThread
{
    Q_OBJECT
public:
    void run();

private:

 signals:
    void emitsignal(const QString &string);
};

class CH9326DEBUG : public QWidget, public Ui::CH9326Dlg
{
    Q_OBJECT

public:
    explicit CH9326DEBUG(QWidget *parent = 0);
    ~CH9326DEBUG();
protected:
    void initDialog();
    void readSettings();
    void OnCheckRadioState();
    void showMsgError(const QString &string);

public slots:
    void addOutput(const QString& text);
protected slots:
    void saveSettings();
    void setGpioData();
    void setGpioDir();
    void getGpio();
    void openDevice();
    void setConfig();
    void sendData();
    void startReceiveData();
    void stopRcvData();
    void clearRcvArea();

    void outputStateChange();
    void setRadioSignalConnection();
    /*  IO1 */
    void OnRadioIo1Input();
    void OnRadioIo1Output();
    void OnRadioIo1High();
    void OnRadioIo1Low();
    /*  IO2 */
    void OnRadioIo2Input();
    void OnRadioIo2Output();
    void OnRadioIo2High();
    void OnRadioIo2Low();
    /*  IO3 */
    void OnRadioIo3Input();
    void OnRadioIo3Output();
    void OnRadioIo3High();
    void OnRadioIo3Low();
    /*  IO4 */
    void OnRadioIo4Input();
    void OnRadioIo4Output();
    void OnRadioIo4High();
    void OnRadioIo4Low();

private:
    long int mRcvSize;
    bool m_isConnected;
    long long m_sndTotalSize;
    unsigned char m_wIODir;
    unsigned char m_wIOData;
    QString m_outputBuffer;

    MyThread *thread;

};

#endif // CH9326DEBUG_H
