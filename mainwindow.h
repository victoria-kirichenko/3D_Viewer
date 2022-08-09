#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <geometryengine.h>

#include <QEvent>
#include <QFile>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QTextStream>
#include <QThread>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE
class MainWindow : public QMainWindow {
  Q_OBJECT
 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_open_file_clicked();

  void on_to_JPG_clicked();

  void on_translate_left_x_clicked();

  void on_translate_right_x_clicked();

  void on_translate_left_y_clicked();

  void on_translate_right_y_clicked();

  void on_translate_left_z_clicked();

  void on_translate_right_z_clicked();

  void on_rotate_left_x_clicked();

  void on_rotate_right_x_clicked();

  void on_rotate_left_y_clicked();

  void on_rotate_right_y_clicked();

  void on_rotate_left_z_clicked();

  void on_rotate_right_z_clicked();

  void on_scale_left_x_clicked();

  void on_scale_right_x_clicked();

  void on_scale_left_y_clicked();

  void on_scale_right_y_clicked();

  void on_scale_left_z_clicked();

  void on_scale_right_z_clicked();

  void on_scale_left_all_clicked();

  void on_scale_right_all_clicked();

  void on_to_GIF_clicked();

  void on_color_edges_clicked();

  void on_color_back_clicked();

  void on_color_verticles_clicked();

  void on_type_of_protection_activated(int index);

  void on_thickness_of_edges_activated(int index);

  void on_display_of_verticles_activated(int index);

  void on_type_of_edges_activated(int index);

  void on_size_of_verticles_activated(int index);

  void loadSettings(QString);

  void saveSettings();

 private:
  bool check = 0;
  Ui::MainWindow *ui;

};
#endif  // MAINWINDOW_H
