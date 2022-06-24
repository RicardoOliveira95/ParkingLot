#include <glib.h>

int main(){

const gchar *my_glade_file =
    "<interface>
  <requires lib="gtk+" version="3.10"/>
  <object class="GtkWindow" id="window_main">
    <property name="width_request">800</property>
    <property name="height_request">480</property>
    <property name="can_focus">False</property>
    <property name="title" translatable="yes">Mall</property>
    <property name="resizable">False</property>
    <property name="window_position">center-always</property>
    <property name="default_width">800</property>
    <property name="default_height">480</property>
    <property name="decorated">False</property>
    <signal name="destroy" handler="on_window_main_destroy" swapped="no"/>
    <child>
      <object class="GtkBox" id="box1">
        <property name="visible">True</property>
        <property name="can_focus">False</property>
        <property name="border_width">10</property>
        <child>
          <object class="GtkBox" id="box2">
            <property name="width_request">150</property>
            <property name="visible">True</property>
            <property name="can_focus">False</property>
            <property name="orientation">vertical</property>
            <property name="spacing">10</property>
            <property name="homogeneous">True</property>
            <child>
              <object class="GtkButton" id="btn_shop1">
                <property name="label" translatable="yes">➀ Joe's Shoes</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
                <signal name="clicked" handler="on_btn_shop1_clicked" swapped="no"/>
              </object>
              <packing>
                <property name="expand">False</property>
                <property name="fill">True</property>
                <property name="position">0</property>
              </packing>
            </child>
            <child>
              <object class="GtkButton" id="btn_shop2">
                <property name="label" translatable="yes">➁ Coffee Shop</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
                <signal name="clicked" handler="on_btn_shop2_clicked" swapped="no"/>
              </object>
              <packing>
                <property name="expand">False</property>
                <property name="fill">True</property>
                <property name="position">1</property>
              </packing>
            </child>
            <child>
              <object class="GtkButton" id="btn_shop3">
                <property name="label" translatable="yes">➂ Post Office</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
                <signal name="clicked" handler="on_btn_shop3_clicked" swapped="no"/>
              </object>
              <packing>
                <property name="expand">False</property>
                <property name="fill">True</property>
                <property name="position">2</property>
              </packing>
            </child>
            <child>
              <object class="GtkButton" id="btn_shop4">
                <property name="label" translatable="yes">➃ Meg's Clothing</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
                <signal name="clicked" handler="on_btn_shop4_clicked" swapped="no"/>
              </object>
              <packing>
                <property name="expand">False</property>
                <property name="fill">True</property>
                <property name="position">3</property>
              </packing>
            </child>
          </object>
          <packing>
            <property name="expand">False</property>
            <property name="fill">True</property>
            <property name="position">0</property>
          </packing>
        </child>
        <child>
          <object class="GtkImage" id="image1">
            <property name="visible">True</property>
            <property name="can_focus">False</property>
            <property name="margin_left">20</property>
            <property name="pixbuf">../res/mall.svg.png</property>
          </object>
          <packing>
            <property name="expand">False</property>
            <property name="fill">True</property>
            <property name="position">2</property>
          </packing>
        </child>
      </object>
    </child>
  </object>
</interface>";

#extern const gchar *my_glade_file;
result = gtk_builder_add_from_string(builder, my_glade_file, -1, &error);
return 0;
}
