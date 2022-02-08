/*
 * Copyright (C) EdgeTX
 *
 * Based on code named
 *   opentx - https://github.com/opentx/opentx
 *   th9x - http://code.google.com/p/th9x
 *   er9x - http://code.google.com/p/er9x
 *   gruvin9x - http://code.google.com/p/gruvin9x
 *
 * License GPLv2: http://www.gnu.org/licenses/gpl-2.0.html
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include "lcdwidget.h"

void LcdWidget::setData(unsigned char *buf, int width, int height, int depth) {
    lcdBuf = buf;
    lcdWidth = width;
    lcdHeight = height;
    lcdDepth = depth;
    if (depth >= 8)
        lcdSize = (width * height) * ((depth + 7) / 8);
    else
        lcdSize = (width * ((height + 7) / 8)) * depth;

    localBuf = (unsigned char *) malloc(lcdSize);
    memset(localBuf, 0, lcdSize);
}

void LcdWidget::onLcdChanged(bool light) {
    QMutexLocker locker(&lcdMtx);
    lightEnable = light;
    memcpy(localBuf, lcdBuf, lcdSize);
    if (!redrawTimer.isValid() ||
        redrawTimer.hasExpired(LCD_WIDGET_REFRESH_PERIOD)) {
        update();
        redrawTimer.start();
    }
}

void LcdWidget::paintEvent(QPaintEvent *) {
    QPainter p(this);
    QImage img(lcdBuf, lcdWidth, lcdHeight, QImage::Format_RGB16);
    img = img.scaledToWidth(QWidget::width(),Qt::SmoothTransformation);
    p.drawImage(QRect(0,0,QWidget::width(),QWidget::height()),img);
}

void LcdWidget::mouseMoveEvent(QMouseEvent *event) {
    int x = event->pos().x();
    int y =event->pos().y();
    calcAbsPoint(x,y);
    emit touchEvent(TouchSlide,x , y);
}

void LcdWidget::mousePressEvent(QMouseEvent *event) {
    int x = event->pos().x();
    int y =event->pos().y();
    calcAbsPoint(x,y);
    emit touchEvent(TouchDown, x, y);
}

void LcdWidget::mouseReleaseEvent(QMouseEvent *event) {
    int x = event->pos().x();
    int y =event->pos().y();
    calcAbsPoint(x,y);
    emit touchEvent(TouchUp, x, y);
}

void LcdWidget::calcAbsPoint(int &x,int &y){
    x = (int)(1.0*x*lcdWidth/QWidget::width());
    y = (int)(1.0*y*lcdHeight/QWidget::height());
}