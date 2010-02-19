/***************************************************************************
    begin       : Mon Feb 15 2010
    copyright   : (C) 2010 by Martin Preuss
    email       : martin@libchipcard.de

 ***************************************************************************
 *          Please see toplevel file COPYING for license details           *
 ***************************************************************************/


#ifndef QT4_GUI_H
#define QT4_GUI_H

class QT4_Gui;
class QWidget;


#include <gwen-gui-qt4/cppgui.hpp>

#include <QString>

#include <string>


class QT4GUI_API QT4_Gui: public CppGui {

private:
  QWidget *_parentWidget;
  std::list<QWidget*> _pushedParents;

public:
  QT4_Gui();
  virtual ~QT4_Gui();


  QWidget *getParentWidget() const { return _parentWidget;};

  void pushParentWidget(QWidget *w);
  void popParentWidget();

  static QString extractHtml(const char *text);

protected:
  /** @name User Interaction
   *
   */
  /*@{*/

  virtual int execDialog(GWEN_DIALOG *dlg, uint32_t guiid);

  virtual int openDialog(GWEN_DIALOG *dlg, uint32_t guiid);
  virtual int closeDialog(GWEN_DIALOG *dlg);
  virtual int runDialog(GWEN_DIALOG *dlg, int untilEnd);

  virtual int getFileName(const char *caption,
			  GWEN_GUI_FILENAME_TYPE fnt,
			  uint32_t flags,
			  const char *patterns,
			  GWEN_BUFFER *pathBuffer,
			  uint32_t guiid);

};



#endif