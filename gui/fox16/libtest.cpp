
#undef BUILDING_FOX16_GUI


#include <gwen-gui-fox16/fox16_gui.hpp>
#include "fox16_htmlctx.hpp"

#include <gwenhywfar/debug.h>


#if 0
int test1(int argc, char **argv) {
  FXApp a("libtest","Martin Preuss");
  FH_HtmlLabel *label;
  FXDialogBox *dbox;
  FXVerticalFrame *vf;
  const char testString[]=
    "<h1>Title</h1>"
    "<h2>Subtitle</h2>"
    "thisIsALongWord <i>and</i> this is <b>bold</b><br>"
    "This should begin on the <b>next</b> line."
    "<p>This should be another paragraph</p>"
    "<p>And this is <i>after</i> the <font color=red>paragraph</font>.</p>";

  a.init(argc,argv);
  a.create();

  dbox=new FXDialogBox(&a, "Test", DECOR_ALL);
  vf=new FXVerticalFrame(dbox, LAYOUT_FILL_X | LAYOUT_FILL_Y,
                         0, 0, 0, 0, 1, 1, 1, 1);
  label=new FH_HtmlLabel(vf, FXString(testString), LAYOUT_FILL_X|LAYOUT_FILL_Y);

  dbox->create();
  dbox->resize(300, 200);
  dbox->show();
  a.runModalFor(dbox);

  return 0;
}
#endif


int test1(int argc, char **argv) {
  FXApp a("libtest","Martin Preuss");
  int rv;
  const char testString[]=
    "This is <b>a</b> test."
    "And this, is the second line:followed by something else."
    "<table>"
    "  <tr>"
    "    <th>header1</th>"
    "    <th>header2</th>"
    "  </tr>"
    "  <tr>"
    "    <td>data1</td>"
    "    <td>data2</td>"
    "  </tr>"
    "</table>"
    "And   this is   after the table.<br>"
    "and this <font color=\"red\">one</font> is red.";

  a.init(argc,argv);
  a.create();

  FOX16_HtmlCtx ctx(0, 0, 2000);
  ctx.setText(testString);
  rv=ctx.layout(1024, 1024);
  fprintf(stderr, "Result of layout: %d\n", rv);
  ctx.dump();

  return 0;
}




int test2(int argc, char **argv) {
  FXApp application("libtest","Martin Preuss");
  FOX16_Gui *gui;
  int rv;
  uint32_t id1;
  uint32_t id2;
  uint64_t i1;
  uint64_t i2;

  application.init(argc,argv);

  application.create();

  gui=new FOX16_Gui(&application);
  GWEN_Gui_SetGui(gui->getCInterface());

  id1=GWEN_Gui_ProgressStart(GWEN_GUI_PROGRESS_SHOW_LOG |
			     GWEN_GUI_PROGRESS_SHOW_ABORT |
			     GWEN_GUI_PROGRESS_KEEP_OPEN,
			     "Progress-Title",
                             "<html>"
                             "<p><b>This</b> is an example <i>text</i>..</p>"
                             "<p>As you can see <font color=red>colors</font> can "
                             "be used.</p>"
                             "</html>",
                             10,
                             0);
  for (i1=1; i1<=10; i1++) {
    char numbuf[128];

    snprintf(numbuf, sizeof(numbuf)-1, "Step %d", (int)i1);
    GWEN_Gui_ProgressLog(id1, GWEN_LoggerLevel_Notice, numbuf);
    id2=GWEN_Gui_ProgressStart(GWEN_GUI_PROGRESS_SHOW_LOG |
                               GWEN_GUI_PROGRESS_DELAY |
			       GWEN_GUI_PROGRESS_SHOW_ABORT,
			       "2nd progress",
			       "Starting 2nd progress...",
			       10,
			       id1);
    for (i2=1; i2<=10; i2++) {
      sleep(1);
      fprintf(stderr, "Advancing %d/%d\n", (int)i1, (int)i2);
      rv=GWEN_Gui_ProgressAdvance(id2, i2);
      if (rv==GWEN_ERROR_USER_ABORTED) {
	fprintf(stderr, "Aborted by user\n");
	break;
      }
    }
    GWEN_Gui_ProgressEnd(id2);

    rv=GWEN_Gui_ProgressAdvance(id1, i1);
    if (rv==GWEN_ERROR_USER_ABORTED) {
      fprintf(stderr, "Aborted by user\n");
      break;
    }
  }

  GWEN_Gui_ProgressEnd(id1);

  return 0;
}




int main(int argc, char **argv) {
  return test1(argc, argv);
}


