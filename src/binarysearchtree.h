/* This file is part of aanalyzer.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <QObject>

class BinarySearchTree : public QObject
{
    Q_OBJECT
public:
    explicit BinarySearchTree(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // BINARYSEARCHTREE_H
