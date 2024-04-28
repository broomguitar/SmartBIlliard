#ifndef LOGIN_H
#define LOGIN_H
#include <QDialog>
#include <QMouseEvent>
namespace Ui {
class Login;
}
class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
    //设置鼠标按下可移动窗口的区域，在子窗口中必须设置该区域
    void setAreaMovable(const QRect rt);
protected:
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
private slots:
    void on_pushButton_login_clicked();

private:
    Ui::Login *ui;
    QRect m_areaMovable;//可移动窗口的区域，鼠标只有在该区域按下才能移动窗口
    bool m_bPressed;//鼠标按下标志（不分左右键）
    QPoint m_ptPress;//鼠标按下的初始位置
};

#endif // LOGIN_H
