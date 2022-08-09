#include "mainwindow.h"

#include <QFutureWatcher>
#include <QtConcurrent>
#include <iostream>

#include "ui_mainwindow.h"
using namespace std;

int check_open = 0;
struct data temp;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->openGLWidget->update();
  loadSettings("/new_settings.cfg");
}

MainWindow::~MainWindow() {
  saveSettings();
  delete ui;
}

void MainWindow::on_open_file_clicked() {
  QString file_path = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.*");
  if (!file_path.isEmpty() && file_path.endsWith(".obj")) {
    if (check == 0) {
      check = 1;
    } else {
      remove_matrix(&ui->openGLWidget->geometries->file);
      ui->openGLWidget->geometries->vertices.clear();
      ui->openGLWidget->geometries->indices.clear();
    }
    QFileInfo file_info(file_path);
    QString file_name = file_info.fileName();
    QByteArray ba = file_path.toLocal8Bit();
    char *str = ba.data();
    ui->openGLWidget->geometries->file = start(str);
    ui->file_name->setText(file_name);
    ui->num_of_verticles->setText(
        QString::number(ui->openGLWidget->geometries->file.count_of_vertexes));
    ui->num_of_edges->setText(
        QString::number(ui->openGLWidget->geometries->file.count_of_facets));
    ui->tr_x->setText("0.00");
    ui->tr_y->setText("0.00");
    ui->tr_z->setText("0.00");
    ui->rot_x->setText("0.00");
    ui->rot_y->setText("0.00");
    ui->rot_z->setText("0.00");
    ui->sc_x->setText("0.00");
    ui->sc_y->setText("0.00");
    ui->sc_z->setText("0.00");
    ui->sc_all->setText("0.00");
  }
  on_display_of_verticles_activated(ui->display_of_verticles->currentIndex());
  on_size_of_verticles_activated(ui->size_of_verticles->currentIndex());
  ui->openGLWidget->geometries->initCubeGeometry();
}

void MainWindow::on_translate_left_x_clicked() {
  move_x(&(ui->openGLWidget->geometries->file.matrix_3d), -0.5);
  double temp = ui->tr_x->text().toDouble() - 0.5;
  QString str = QString("%1").arg(temp);
  ui->tr_x->setText(str);
  ui->openGLWidget->update();
}

void MainWindow::on_translate_right_x_clicked() {
  move_x(&(ui->openGLWidget->geometries->file.matrix_3d), 0.5);
  double temp = ui->tr_x->text().toDouble() + 0.5;
  QString str = QString("%1").arg(temp);
  ui->tr_x->setText(str);
  ui->openGLWidget->update();
}

void MainWindow::on_translate_left_y_clicked() {
  move_y(&(ui->openGLWidget->geometries->file.matrix_3d), -0.5);
  double temp = ui->tr_y->text().toDouble() - 0.5;
  QString str = QString("%1").arg(temp);
  ui->tr_y->setText(str);
  ui->openGLWidget->update();
}

void MainWindow::on_translate_right_y_clicked() {
  move_y(&(ui->openGLWidget->geometries->file.matrix_3d), 0.5);
  double temp = ui->tr_y->text().toDouble() + 0.5;
  QString str = QString("%1").arg(temp);
  ui->tr_y->setText(str);
  ui->openGLWidget->update();
}

void MainWindow::on_translate_left_z_clicked() {
  move_z(&(ui->openGLWidget->geometries->file.matrix_3d), -0.5);
  double temp = ui->tr_z->text().toDouble() - 0.5;
  QString str = QString("%1").arg(temp);
  ui->tr_z->setText(str);
  ui->openGLWidget->update();
}

void MainWindow::on_translate_right_z_clicked() {
  move_z(&(ui->openGLWidget->geometries->file.matrix_3d), 0.5);
  double temp = ui->tr_z->text().toDouble() + 0.5;
  QString str = QString("%1").arg(temp);
  ui->tr_z->setText(str);
  ui->openGLWidget->update();
}

void MainWindow::on_rotate_left_x_clicked() {
  rotation_x(&(ui->openGLWidget->geometries->file.matrix_3d), -10.5);
  double temp = ui->rot_x->text().toDouble() - 10.5;
  QString str = QString("%1").arg(temp);
  ui->rot_x->setText(str);
  ui->openGLWidget->update();
}

void MainWindow::on_rotate_right_x_clicked() {
  rotation_x(&(ui->openGLWidget->geometries->file.matrix_3d), 10.5);
  double temp = ui->rot_x->text().toDouble() + 10.5;
  QString str = QString("%1").arg(temp);
  ui->rot_x->setText(str);
  ui->openGLWidget->update();
}

void MainWindow::on_rotate_left_y_clicked() {
  rotation_y(&(ui->openGLWidget->geometries->file.matrix_3d), -10.5);
  double temp = ui->rot_y->text().toDouble() - 10.5;
  QString str = QString("%1").arg(temp);
  ui->rot_y->setText(str);
  ui->openGLWidget->update();
}

void MainWindow::on_rotate_right_y_clicked() {
  rotation_y(&(ui->openGLWidget->geometries->file.matrix_3d), 10.5);
  double temp = ui->rot_y->text().toDouble() + 10.5;
  QString str = QString("%1").arg(temp);
  ui->rot_y->setText(str);
  ui->openGLWidget->update();
}

void MainWindow::on_rotate_left_z_clicked() {
  rotation_z(&(ui->openGLWidget->geometries->file.matrix_3d), -10.5);
  double temp = ui->rot_z->text().toDouble() - 10.5;
  QString str = QString("%1").arg(temp);
  ui->rot_z->setText(str);
  ui->openGLWidget->update();
}

void MainWindow::on_rotate_right_z_clicked() {
  rotation_z(&(ui->openGLWidget->geometries->file.matrix_3d), 10.5);
  double temp = ui->rot_z->text().toDouble() + 10.5;
  QString str = QString("%1").arg(temp);
  ui->rot_z->setText(str);
  ui->openGLWidget->update();
}

void MainWindow::on_scale_left_x_clicked() {
  scale_x(&(ui->openGLWidget->geometries->file.matrix_3d), -1.5);
  double temp = ui->sc_x->text().toDouble() - 1.5;
  QString str = QString("%1").arg(temp);
  ui->sc_x->setText(str);
  ui->openGLWidget->update();
}

void MainWindow::on_scale_right_x_clicked() {
  scale_x(&(ui->openGLWidget->geometries->file.matrix_3d), 1.5);
  double temp = ui->sc_x->text().toDouble() + 1.5;
  QString str = QString("%1").arg(temp);
  ui->sc_x->setText(str);
  ui->openGLWidget->update();
}

void MainWindow::on_scale_left_y_clicked() {
  scale_y(&(ui->openGLWidget->geometries->file.matrix_3d), -1.5);
  double temp = ui->sc_y->text().toDouble() - 1.5;
  QString str = QString("%1").arg(temp);
  ui->sc_y->setText(str);
  ui->openGLWidget->update();
}

void MainWindow::on_scale_right_y_clicked() {
  scale_y(&(ui->openGLWidget->geometries->file.matrix_3d), 1.5);
  double temp = ui->sc_y->text().toDouble() + 1.5;
  QString str = QString("%1").arg(temp);
  ui->sc_y->setText(str);
  ui->openGLWidget->update();
}

void MainWindow::on_scale_left_z_clicked() {
  scale_z(&(ui->openGLWidget->geometries->file.matrix_3d), -1.5);
  double temp = ui->sc_z->text().toDouble() - 1.5;
  QString str = QString("%1").arg(temp);
  ui->sc_z->setText(str);
  ui->openGLWidget->update();
}

void MainWindow::on_scale_right_z_clicked() {
  scale_z(&(ui->openGLWidget->geometries->file.matrix_3d), 1.5);
  double temp = ui->sc_z->text().toDouble() + 1.5;
  QString str = QString("%1").arg(temp);
  ui->sc_z->setText(str);
  ui->openGLWidget->update();
}

void MainWindow::on_scale_left_all_clicked() {
  scale_xyz(&(ui->openGLWidget->geometries->file.matrix_3d), 0.5);
  double temp = ui->sc_all->text().toDouble() - 0.5;
  QString str = QString("%1").arg(temp);
  ui->sc_all->setText(str);
  ui->openGLWidget->update();
}

void MainWindow::on_scale_right_all_clicked() {
  scale_xyz(&(ui->openGLWidget->geometries->file.matrix_3d), -0.5);
  double temp = ui->sc_all->text().toDouble() + 0.5;
  QString str = QString("%1").arg(temp);
  ui->sc_all->setText(str);
  ui->openGLWidget->update();
}

void MainWindow::on_to_GIF_clicked() { ui->openGLWidget->setTimer(); }

void MainWindow::on_to_JPG_clicked() {
  QString type = "";
  QMessageBox::StandardButton reply;
  reply =
      QMessageBox::question(this, "Whot do you want?", "No - JPG, Yes - BMP",
                            QMessageBox::Yes | QMessageBox::No);
  if (reply == QMessageBox::Yes) {
    type = "bmp (*.bmp)";
  } else if (reply == QMessageBox::No) {
    type = "jpg (*.jpg)";
  }
  QFileDialog file_dialog_photo(this);
  QString f_name_photo =
      file_dialog_photo.getSaveFileName(this, tr("Save a gif"), "", type);
  QFile file(f_name_photo);
  file.open(QIODevice::WriteOnly);
  QRect rect(0, 0, ui->openGLWidget->width(), ui->openGLWidget->height());
  QPixmap pixmap = ui->openGLWidget->grab(rect);
  pixmap.copy(rect);
  pixmap.toImage().save(&file, "jpg");
  QString q_command_line = "open " + f_name_photo;
  QByteArray temp = q_command_line.toLocal8Bit();
  char *command_line = temp.data();
  system(command_line);
}

void MainWindow::on_color_edges_clicked() {
  *ui->openGLWidget->color = QColorDialog::getColor();
  ui->openGLWidget->paintGL();
  ui->openGLWidget->update();
}

void MainWindow::on_color_back_clicked() {
  *ui->openGLWidget->color_back = QColorDialog::getColor();
  ui->openGLWidget->paintGL();
  ui->openGLWidget->update();
}

void MainWindow::on_color_verticles_clicked() {
  *ui->openGLWidget->color_ver = QColorDialog::getColor();
  ui->openGLWidget->update();
}

void MainWindow::on_type_of_protection_activated(int index) {
  ui->openGLWidget->check_projection = index;
  ui->openGLWidget->resizeGL(640, 480);
  ui->openGLWidget->update();
}

void MainWindow::on_thickness_of_edges_activated(int index) {
  ui->openGLWidget->line_width =
      ui->thickness_of_edges->currentText().toDouble();
  ui->openGLWidget->update();
}

void MainWindow::on_display_of_verticles_activated(int index) {
  ui->openGLWidget->geometries->dot_type = index;
  ui->openGLWidget->update();
}

void MainWindow::on_size_of_verticles_activated(int index) {
  ui->openGLWidget->geometries->size_vert =
      ui->size_of_verticles->currentText().toInt();
  ui->openGLWidget->update();
}

void MainWindow::on_type_of_edges_activated(int index) {
  ui->openGLWidget->line_type = index;
  ui->openGLWidget->update();
}

void MainWindow::saveSettings() {
  QString path;
  path += QCoreApplication::applicationDirPath();
  path += "/new_settings.cfg";
  QFile file(path);
  if (file.open(QIODevice::ReadWrite)) {
    QTextStream t_stream(&file);
    t_stream.flush();
    t_stream << ui->type_of_protection->currentIndex() << '\n';
    t_stream << ui->type_of_edges->currentIndex() << '\n';
    t_stream << ui->thickness_of_edges->currentIndex() << '\n';
    t_stream << ui->display_of_verticles->currentIndex() << '\n';
    t_stream << ui->size_of_verticles->currentIndex() << '\n';
    int red, green, blue, alpha;
    ui->openGLWidget->color->getRgb(&red, &green, &blue, &alpha);
    t_stream << red << ' ' << green << ' ' << blue << ' ' << alpha << '\n';
    ui->openGLWidget->color_back->getRgb(&red, &green, &blue, &alpha);
    t_stream << red << ' ' << green << ' ' << blue << ' ' << alpha << '\n';
    ui->openGLWidget->color_ver->getRgb(&red, &green, &blue, &alpha);
    t_stream << red << ' ' << green << ' ' << blue << ' ' << alpha << '\n';
    file.close();
  }
}

void MainWindow::loadSettings(QString str) {
  ui->openGLWidget->update();
  QString path = "";
  if (str[0] != ':') path = QCoreApplication::applicationDirPath();
  path += str;
  QFile file(path);
  if (file.open(QIODevice::ReadOnly)) {
    QTextStream t_stream(&file);
    QString str = t_stream.readLine();
    ui->type_of_protection->setCurrentIndex(str.toInt());
    on_type_of_protection_activated(ui->type_of_protection->currentIndex());

    str = t_stream.readLine();
    ui->type_of_edges->setCurrentIndex(str.toInt());
    on_type_of_edges_activated(ui->type_of_edges->currentIndex());

    str = t_stream.readLine();
    ui->thickness_of_edges->setCurrentIndex(str.toInt());
    on_thickness_of_edges_activated(ui->thickness_of_edges->currentIndex());

    str = t_stream.readLine();
    ui->display_of_verticles->setCurrentIndex(str.toInt());

    str = t_stream.readLine();
    ui->size_of_verticles->setCurrentIndex(str.toInt());

    str = t_stream.readLine();
    QList<QString> clr = str.split(' ');
    ui->openGLWidget->color->setRgb(clr[0].toInt(), clr[1].toInt(),
                                    clr[2].toInt(), clr[3].toInt());
    clr.clear();
    str = t_stream.readLine();
    clr = str.split(' ');
    ui->openGLWidget->color_back->setRgb(clr[0].toInt(), clr[1].toInt(),
                                         clr[2].toInt(), clr[3].toInt());
    clr.clear();
    str = t_stream.readLine();
    clr = str.split(' ');
    ui->openGLWidget->color_ver->setRgb(clr[0].toInt(), clr[1].toInt(),
                                        clr[2].toInt(), clr[3].toInt());
    file.close();
  }
  ui->openGLWidget->update();
}
