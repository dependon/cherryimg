/*
 * Copyright (C) 2020 ~ 2021 Uniontech Software Technology Co., Ltd.
 *
 * Author:     LiuMingHang <liuminghang@uniontech.com>
 *
 * Maintainer: ZhangYong <ZhangYong@uniontech.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "imagebutton.h"
//#include "application.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QFrame>
#include <QFile>
#include <QHelpEvent>
#include <QDebug>
#include <QHBoxLayout>
#include <QTimer>

typedef QFrame QFrToDFrame;

ImageButton::ImageButton(QWidget *parent)
    : QToolButton(parent), m_tooltipVisiable(false)
{
//    onThemeChanged(dApp->viewerTheme->getCurrentTheme());
//    connect(dApp->viewerTheme, &ViewerThemeManager::viewerThemeChanged, this,
//            &ImageButton::onThemeChanged);
}

ImageButton::ImageButton(const QString &normalPic, const QString &hoverPic,
                         const QString &pressPic, const QString &disablePic,
                         QWidget *parent)
    : QToolButton( parent)
    , m_tooltipVisiable(false)
    , m_disablePic_(disablePic)
{
//    onThemeChanged(dApp->viewerTheme->getCurrentTheme());
//    connect(dApp->viewerTheme, &ViewerThemeManager::viewerThemeChanged, this,
//            &ImageButton::onThemeChanged);
}


void ImageButton::setDisabled(bool d)
{
//    if (d) {
//        setNormalPic(m_disablePic_);
//    }
//    else {
//        setNormalPic(this->getNormalPic());
//    }
    QToolButton::setDisabled(d);
}

bool ImageButton::event(QEvent *e)
{
    if (e->type() == QEvent::ToolTip) {
        if (QHelpEvent *he = static_cast<QHelpEvent *>(e)) {
            showTooltip(he->globalPos());

            return false;
        }
    } else if (e->type() == QEvent::Leave)  {
        emit mouseLeave();
        QToolButton::leaveEvent(e);
    } else if (e->type() == QEvent::MouseButtonPress) {
        emit mouseLeave();

    }

    return QToolButton::event(e);
}

//void ImageButton::onThemeChanged(ViewerThemeManager::AppTheme theme)
//{
//    Q_UNUSED(theme);
//}

void ImageButton::setTooltipVisible(bool visible)
{
    m_tooltipVisiable = visible;
}


void ImageButton::enterEvent(QEvent *e)
{
    if (isEnabled()) {
        QToolButton::enterEvent(e);
    }
}

void ImageButton::showTooltip(const QPoint &gPos)
{
    if (toolTip().trimmed().isEmpty() || m_tooltipVisiable) {
        return;
    } else {
        m_tooltipVisiable = true;
    }

    QFrToDFrame *tf = new QFrToDFrame();
//    tf->setStyleSheet(this->styleSheet());
    tf->setWindowFlags(Qt::ToolTip);
    tf->setAttribute(Qt::WA_TranslucentBackground);
    QLabel *tl = new QLabel(tf);
    tl->setObjectName("ButtonTooltip");
    tl->setText(toolTip());
    QHBoxLayout *layout = new QHBoxLayout(tf);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(tl);

    tf->show();
    QRect dr = qApp->desktop()->geometry();
    int y = gPos.y() + tf->height();
    if (y > dr.y() + dr.height()) {
        y = gPos.y() - tf->height() - 10;
    }
    tf->move(gPos.x() - tf->width() / 3, y - tf->height() / 3);

    QTimer::singleShot(5000, tf, SLOT(deleteLater()));

    connect(tf, &QFrToDFrame::destroyed, this, [ = ] {
        m_tooltipVisiable = false;
    });

    connect(this, &ImageButton::mouseLeave, tf, &QFrToDFrame::deleteLater);
}
