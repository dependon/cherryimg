/*
 * Copyright (C) 2020 ~ 2021 Uniontech Software Technology Co., Ltd.
 *
 * Author:     ZhangYong <zhangyong@uniontech.com>
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

#ifndef TOPTOOLBAR_H
#define TOPTOOLBAR_H

#include "abstracttoptoolbar.h"

#include <QJsonObject>
#include <QPointer>
#include <QLabel>
#include <QGraphicsDropShadowEffect>
#include <QMenu>
#include <QLabel>
#include <QGuiApplication>

class SettingsWindow;
class QHBoxLayout;

class LibTopToolbar : public AbstractTopToolbar
{
    Q_OBJECT
public:
    LibTopToolbar(bool manager, QWidget *parent);
    void setMiddleContent(const QString &path) override;
public slots:
    void setTitleBarTransparent(bool a) override;
protected:
    void mouseDoubleClickEvent(QMouseEvent *e) override;
    void paintEvent(QPaintEvent *e) override;
    void resizeEvent(QResizeEvent *event) override;
    void leaveEvent(QEvent *event) override;
signals:
    void updateMaxBtn();
private:
    enum MenuItemId {
        IdCreateAlbum,
        IdSwitchTheme,
        IdSetting,
        IdImport,
        IdHelp,
        IdAbout,
        IdQuick,
        IdSeparator
    };
    void initMenu();
    void initWidgets();
    QString  geteElidedText(QFont font, QString str, int MaxWidth);

private slots:
    //void onThemeTypeChanged();
    //void onUpdateFileName(const QString &filename);

private:
    QColor m_coverBrush;
    QColor m_topBorderColor;
    QColor m_bottomBorderColor;
    QHBoxLayout *m_layout = nullptr;
    QHBoxLayout *m_lLayout = nullptr;
    QHBoxLayout *m_mLayout = nullptr;
    QHBoxLayout *m_rLayout = nullptr;
    QWidget *m_titlebar = nullptr;
    QLabel *m_titletxt = nullptr;
    QString m_filename;
    QMenu *m_menu;
    bool m_manager;

    bool m_viewChange;
    QGraphicsDropShadowEffect *shadowEffect {nullptr};
};

#endif // TOPTOOLBAR_H
