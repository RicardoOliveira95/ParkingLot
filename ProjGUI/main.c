#include <stdlib.h>
#include <gtk/gtk.h>
#include <glib.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<conio.h>
#include<stdbool.h>
#include<string.h>

#define MAX_LIN 200
#define MAX_COL 200
#define MAX_PIS 5

typedef struct {
	int llinha;
	int lcoluna;
	int lpiso;
	time_t h_inicio;
	time_t h_fim;
	double diff_t;
	bool estado;
	char* matricula;
} Lugar;

typedef struct {
	int lin;
	int col;
	int pis;
	Lugar Lugar1[MAX_PIS][MAX_LIN][MAX_COL];
	float preco;
	bool existe;
} Parque;

Parque Parque1;
char *matr;
//Parque1.existe=false;

GtkWidget *button1,*button2,*button3,*button4,*label,*img;
GtkWidget *label1,*label2,*label3,*label4,*label5,*label6,*entry1,*entry2,*entry3,*entry4;
GtkTooltips *tooltips;
FILE *fparques;

static void helloWorld (GtkWidget *wid, GtkWidget *win)
{
  GtkWidget *dialog = NULL;

  dialog = gtk_message_dialog_new (GTK_WINDOW (win), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, "Estacionar veiculo!");
  gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
  gtk_dialog_run (GTK_DIALOG (dialog));
  gtk_widget_destroy (dialog);
}

static void destroy(GtkWidget *widget, gpointer data)
{
    gtk_main_quit();
}

static void cancelar(GtkWidget *widget, gpointer data)
{
    gtk_main_quit();
}

static void criar(GtkWidget *widget, gpointer data){
    if(Parque1.existe==false){
    Parque1.pis=atoi(gtk_entry_get_text(entry1));
    Parque1.lin=atoi(gtk_entry_get_text(entry2));
    Parque1.col=atoi(gtk_entry_get_text(entry3));
    Parque1.existe=true;
    Parque1.preco=atof(gtk_entry_get_text(entry4));
    int i,j,k;
    for(k=1;k<Parque1.pis+1;k++)
        for(i=1;i<Parque1.lin+1;i++)
            for(j=1;j<Parque1.col+1;j++){
                Parque1.Lugar1[k][i][j].estado=false;
                Parque1.Lugar1[k][i][j].matricula=" ";}

    GtkWidget *popup;
    popup=gtk_message_dialog_new(GTK_WINDOW(data),
                                 GTK_DIALOG_DESTROY_WITH_PARENT,
                                 GTK_MESSAGE_INFO,
                                 GTK_BUTTONS_OK,
                                 "Parque criado com sucesso!");
  gtk_window_set_title(GTK_WINDOW(popup), "Information");
  gtk_dialog_run(GTK_DIALOG(popup));
  gtk_widget_destroy(popup);}

  else{
    GtkWidget *popup;
    popup=gtk_message_dialog_new(GTK_WINDOW(data),
                                 GTK_DIALOG_DESTROY_WITH_PARENT,
                                 GTK_MESSAGE_ERROR,
                                 GTK_BUTTONS_OK,
                                 "Ainda tem um parque com lugares ocupados!");
  gtk_window_set_title(GTK_WINDOW(popup), "Information");
  gtk_dialog_run(GTK_DIALOG(popup));
  gtk_widget_destroy(popup);
  }
  toString();
}

bool apagar(GtkWidget *widget, gpointer data){
    if(Parque1.existe){
            Parque1.existe=false;
            Parque1.col=0;
            Parque1.lin=0;
            Parque1.preco=0;
            GtkWidget *popup;
        popup=gtk_message_dialog_new(GTK_WINDOW(data),
                                     GTK_DIALOG_DESTROY_WITH_PARENT,
                                     GTK_MESSAGE_INFO,
                                     GTK_BUTTONS_OK,
                                     "Parque apagado com sucesso!");
      gtk_window_set_title(GTK_WINDOW(popup), "Information");
      gtk_dialog_run(GTK_DIALOG(popup));
      gtk_widget_destroy(popup);
    }
    else{
      //entry4=gtk_entry_new();
      GtkWidget *popup;
        popup=gtk_message_dialog_new(GTK_WINDOW(data),
                                     GTK_DIALOG_DESTROY_WITH_PARENT,
                                     GTK_MESSAGE_ERROR,
                                     GTK_BUTTONS_OK,
                                     "Ainda não tem um parque criado!");
      gtk_window_set_title(GTK_WINDOW(popup), "Information");
      gtk_dialog_run(GTK_DIALOG(popup));
      gtk_widget_destroy(popup);
    }
}

bool read_file(GtkFileSelection *fs){
    char buff[255];

	fparques=fopen(gtk_file_selection_get_filename (GTK_FILE_SELECTION (fs)),"r");

	if(fparques==NULL){
    perror("Unable to open file!");
    return false;
        exit(1);
	}
    int i=0;
	while(fgets(buff,sizeof(buff),fparques)!=NULL){
        fputs(buff,stdout);
        fputs("|*\n",stdout);

        if(i==0)
            Parque1.pis=atoi(buff);
        else if(i==1)
            Parque1.lin=atoi(buff);
        else if(i==2)
            Parque1.col=atoi(buff);
        else if(i==3)
            Parque1.preco=atoi(buff);
        else
            return false;
        i++;
	}
	fclose(fparques);
	Parque1.existe=true;

	int j,k;
    for(k=1;k<Parque1.pis+1;k++)
        for(i=1;i<Parque1.lin+1;i++)
            for(j=1;j<Parque1.col+1;j++)
                Parque1.Lugar1[k][i][j].estado=false;

    toString();
    return true;
}

void file_ok_sel (GtkWidget *w, GtkFileSelection *fs)
{
    if(read_file(fs)){
        GtkWidget *popup;
        popup=gtk_message_dialog_new(GTK_WINDOW(fs),
                                     GTK_DIALOG_DESTROY_WITH_PARENT,
                                     GTK_MESSAGE_INFO,
                                     GTK_BUTTONS_OK,
                                     "Parque carregado com sucesso!");
      gtk_window_set_title(GTK_WINDOW(popup), "Information");
      gtk_dialog_run(GTK_DIALOG(popup));
      gtk_widget_destroy(popup);
    }
    ///g_print ("%s\n", gtk_file_selection_get_filename (GTK_FILE_SELECTION (fs)));
}

static void carregar(GtkWidget *widget,gpointer data){
    GtkWidget *filew;
    if(Parque1.existe){
    /* Create a new file selection widget */
    filew = gtk_file_selection_new ("File selection");

    gtk_signal_connect (GTK_OBJECT (filew), "destroy",
                        (GtkSignalFunc) destroy, &filew);
    /* Connect the ok_button to file_ok_sel function */
    gtk_signal_connect (GTK_OBJECT (GTK_FILE_SELECTION (filew)->ok_button),
                        "clicked", (GtkSignalFunc) file_ok_sel, filew );

    /* Connect the cancel_button to destroy the widget */
    gtk_signal_connect_object (GTK_OBJECT (GTK_FILE_SELECTION (filew)->cancel_button),
                               "clicked", (GtkSignalFunc) gtk_widget_destroy,
                               GTK_OBJECT (filew));
    gtk_widget_show(filew);}

    else{
        GtkWidget *popup;
        popup=gtk_message_dialog_new(GTK_WINDOW(data),
                                     GTK_DIALOG_DESTROY_WITH_PARENT,
                                     GTK_MESSAGE_ERROR,
                                     GTK_BUTTONS_OK,
                                     "Ainda nao seleccionou um parque!");
      gtk_window_set_title(GTK_WINDOW(popup), "Information");
      gtk_dialog_run(GTK_DIALOG(popup));
      gtk_widget_destroy(popup);
     }
}

bool matUnica(mat){
    char *str=malloc(6);
    matr=malloc(6);
    matr=mat;
    int i,j,k;
    for(k=1;k<Parque1.pis+1;k++)
        for(i=1;i<Parque1.lin+1;i++)
            for(j=1;j<Parque1.col+1;j++){
                    printf("\n%d%d%d:%s,%s",k,i,j,Parque1.Lugar1[k][i][j].matricula,matr);
                if(strcmp(Parque1.Lugar1[k][i][j].matricula,matr)==0)

                    return false;}
    printf("MATRICULA");
    return true;
}

bool checkMat(mat){
    //printf(matUnica(mat));
    if(strlen(mat)==6){
        int i,letters=0,nums=0;
        char buffer[20];
        char *str=malloc(6);
        str=mat;
        //printf("%s",str);
        //printf("%c \n",itoa(mat,buffer,10));

        for(i=0;i<strlen(mat);i++){
            if(isalpha(str[i]))
                letters+=1;
            if(isdigit(str[i]))
                nums+=1;
        }
        //printf("%d,%d",letters,nums);
        if((letters==2&&nums==4||letters==4&&nums==2)&&matUnica(str))
                //printf("MATRICULA");
            return true;
        }
    else
        return false;
}

bool checkForMat(mat){
    //PROCURAR MATRICULA
    int i,j,k;
    char *str=malloc(6);
    char *str1=malloc(6);
    str=mat;
    char buff[2];

    for(k=1;k<Parque1.pis+1;k++){
        for(i=1;i<Parque1.lin+1;i++){
            for(j=1;j<Parque1.col+1;j++){
                    printf("\nMATRICULA: %s",Parque1.Lugar1[k][i][j].matricula);
                    str1=Parque1.Lugar1[k][i][j].matricula;
                    printf("\n%d%d%d: %s,%s",k,i,j,str1,str);
                if(Parque1.Lugar1[k][i][j].estado&&strcmp(str,str1)==0){
                        printf("\nTirar em: %d,%d,%d",k,i,j);
                    Parque1.Lugar1[k][i][j].lpiso=k;
                    Parque1.Lugar1[k][i][j].llinha=i;
                    Parque1.Lugar1[k][i][j].lcoluna=j;
                    Parque1.Lugar1[k][i][j].estado=false;
                    printf("\nCHECKED!");
                    return true;
                }}}}
    printf("\nNOT CHECKED");
    return false;
}

static void estacionar_carro(GtkWidget *widget,gpointer data){
    char *str=malloc(6);
    str=gtk_entry_get_text(entry4);
    //strcpy(gtk_entry_get_text(entry4),str);
    if(checkMat(gtk_entry_get_text(entry4))&&Parque1.Lugar1[atoi(gtk_entry_get_text(entry1))][atoi(gtk_entry_get_text(entry2))][atoi(gtk_entry_get_text(entry3))].estado==false){
        Parque1.Lugar1[atoi(gtk_entry_get_text(entry1))][atoi(gtk_entry_get_text(entry2))][atoi(gtk_entry_get_text(entry3))].estado=true;
        Parque1.Lugar1[atoi(gtk_entry_get_text(entry1))][atoi(gtk_entry_get_text(entry2))][atoi(gtk_entry_get_text(entry3))].h_inicio=time(NULL);
        Parque1.Lugar1[atoi(gtk_entry_get_text(entry1))][atoi(gtk_entry_get_text(entry2))][atoi(gtk_entry_get_text(entry3))].lpiso=entry1;
        Parque1.Lugar1[atoi(gtk_entry_get_text(entry1))][atoi(gtk_entry_get_text(entry2))][atoi(gtk_entry_get_text(entry3))].llinha=entry2;
        Parque1.Lugar1[atoi(gtk_entry_get_text(entry1))][atoi(gtk_entry_get_text(entry2))][atoi(gtk_entry_get_text(entry3))].lcoluna=entry3;
        Parque1.Lugar1[atoi(gtk_entry_get_text(entry1))][atoi(gtk_entry_get_text(entry2))][atoi(gtk_entry_get_text(entry3))].matricula=str;
        printf("\nESTACIONAR AQUI: %d%d%d ,%s",atoi(gtk_entry_get_text(entry1)),atoi(gtk_entry_get_text(entry2)),atoi(gtk_entry_get_text(entry3)),Parque1.Lugar1[atoi(gtk_entry_get_text(entry1))][atoi(gtk_entry_get_text(entry2))][atoi(gtk_entry_get_text(entry3))].matricula);
        GtkWidget *popup;
        popup=gtk_message_dialog_new(GTK_WINDOW(data),
                                     GTK_DIALOG_DESTROY_WITH_PARENT,
                                     GTK_MESSAGE_INFO,
                                     GTK_BUTTONS_OK,
                                     "Veiculo estacionado com sucesso!");
      gtk_window_set_title(GTK_WINDOW(popup), "Information");
      gtk_dialog_run(GTK_DIALOG(popup));
      gtk_widget_destroy(popup);
      toString();//...
      //entry4=gtk_entry_new();
    }
    else{
      //entry4=gtk_entry_new();
      GtkWidget *popup;
        popup=gtk_message_dialog_new(GTK_WINDOW(data),
                                     GTK_DIALOG_DESTROY_WITH_PARENT,
                                     GTK_MESSAGE_ERROR,
                                     GTK_BUTTONS_OK,
                                     "Por favor introduza uma matricula valida!");
      gtk_window_set_title(GTK_WINDOW(popup), "Information");
      gtk_dialog_run(GTK_DIALOG(popup));
      gtk_widget_destroy(popup);
    }
}

static void retirar_carro(GtkWidget *widget,gpointer data){
    printf("\nMARICULA A RETIRAR: %s",gtk_entry_get_text(entry4));
    if(checkForMat(gtk_entry_get_text(entry4))){
            printf("Tirar carro em: %d,%d,%d",atoi(gtk_entry_get_text(entry1)),atoi(gtk_entry_get_text(entry2)),atoi(gtk_entry_get_text(entry3)));
        //Parque1.Lugar1[atoi(gtk_entry_get_text(entry1))][atoi(gtk_entry_get_text(entry2))][atoi(gtk_entry_get_text(entry3))].estado=true;
        Parque1.Lugar1[atoi(gtk_entry_get_text(entry1))][atoi(gtk_entry_get_text(entry2))][atoi(gtk_entry_get_text(entry3))].h_fim=time(NULL);
        Parque1.Lugar1[atoi(gtk_entry_get_text(entry1))][atoi(gtk_entry_get_text(entry2))][atoi(gtk_entry_get_text(entry3))].diff_t=difftime(Parque1.Lugar1[atoi(gtk_entry_get_text(entry1))][atoi(gtk_entry_get_text(entry2))][atoi(gtk_entry_get_text(entry3))].h_fim,Parque1.Lugar1[atoi(gtk_entry_get_text(entry1))][atoi(gtk_entry_get_text(entry2))][atoi(gtk_entry_get_text(entry3))].h_inicio);

        float preco_pagar = (Parque1.Lugar1[atoi(gtk_entry_get_text(entry1))][atoi(gtk_entry_get_text(entry2))][atoi(gtk_entry_get_text(entry3))].diff_t / 3600.00)*Parque1.preco;
        printf("\n %f",preco_pagar);
        char buff[10];
        double tempo_s = Parque1.Lugar1[atoi(gtk_entry_get_text(entry1))][atoi(gtk_entry_get_text(entry2))][atoi(gtk_entry_get_text(entry3))].diff_t;
        int tempo_m,tempo_h,resto_s;
        GtkWidget *window;//*button;
     window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
     gtk_window_set_title (GTK_WINDOW (window), "RECIBO");

    label1=gtk_label_new("Matricula");
    label2=gtk_label_new(Parque1.Lugar1[atoi(gtk_entry_get_text(entry1))][atoi(gtk_entry_get_text(entry2))][atoi(gtk_entry_get_text(entry3))].matricula);
    label3=gtk_label_new("Tempo");
    if(tempo_s<=60)
        label4=gtk_label_new(gcvt(Parque1.Lugar1[atoi(gtk_entry_get_text(entry1))][atoi(gtk_entry_get_text(entry2))][atoi(gtk_entry_get_text(entry3))].diff_t,10,buff));
    else if(3600<=tempo_s<60){
        tempo_m = (int)tempo_s/60;
		resto_s = (int)tempo_s%60;
		printf("tempos:%d,%d",tempo_m,resto_s);
		char buffer[30],buff[20],*res;
		strcpy(buffer,"Time: ");
		res=strcat(buffer,itoa(tempo_m,buff,10));
		res=strcat(buffer,itoa(resto_s,buff,10));
		printf("\nResultado: %s",res);
		label4=gtk_label_new(res);
    }else{
        tempo_m = (int)tempo_s/60;
		tempo_h = (int)tempo_s/3600;
    }
    label5=gtk_label_new("Preco");
    label6=gtk_label_new(gcvt(preco_pagar,10,buff));

    GtkWidget *box;
    box = gtk_vbox_new(GTK_ORIENTATION_VERTICAL,20);
     gtk_box_pack_start(GTK_BOX(box),label,FALSE,FALSE,0);
     gtk_box_pack_start(GTK_BOX(box),label2,FALSE,FALSE,0);
     gtk_box_pack_start(GTK_BOX(box),label3,FALSE,FALSE,0);
     gtk_box_pack_start(GTK_BOX(box),label4,FALSE,FALSE,0);
     gtk_box_pack_start(GTK_BOX(box),label5,FALSE,FALSE,0);
     gtk_box_pack_start(GTK_BOX(box),label6,FALSE,FALSE,0);

     gtk_container_add(GTK_CONTAINER(window),box);
     gtk_widget_show_all (window);
     toString();
    }
    else{
        GtkWidget *dialog;
        dialog = gtk_message_dialog_new(GTK_WINDOW(data),
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            "Veiculo nao encontrado..");
          gtk_window_set_title(GTK_WINDOW(dialog), "Error");
          gtk_dialog_run(GTK_DIALOG(dialog));
          gtk_widget_destroy(dialog);
    }
}

static void mostrarParque(GtkWidget *widget,gpointer data){
    toString();
}

static void criarParque(GtkWidget *widget,gpointer data){
    //int response;

    /*GtkWidget *dialog = gtk_dialog_new();
    gtk_window_set_title(GTK_WINDOW(dialog), "Criar parque");
    gtk_window_set_default_size(GTK_WINDOW(dialog), 200, 200);
    gtk_dialog_add_button(GTK_DIALOG(dialog), "_Reject", GTK_RESPONSE_REJECT);
    gtk_dialog_add_button(GTK_DIALOG(dialog), "_Accept", GTK_RESPONSE_ACCEPT);
    response = gtk_dialog_run(GTK_DIALOG(dialog));

    if (response == -2)
        printf("Reject button clicked!\n");
    else if (response == -3)
        printf("Accept button clicked!\n");

    gtk_widget_destroy(dialog);*/

    GtkWidget *window;//*button;
     window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
     gtk_window_set_title (GTK_WINDOW (window), "CRIAR NOVO PARQUE");

    label1=gtk_label_new("Pisos");
    entry1=gtk_entry_new();
    label2=gtk_label_new("Linhas");
    entry2=gtk_entry_new();
    label3=gtk_label_new("Colunas");
    entry3=gtk_entry_new();
    label4=gtk_label_new("Preco");
    entry4=gtk_entry_new();
    button1 = gtk_button_new_with_label("Criar parque");
    button2=gtk_button_new_with_label("Carregar parque");
    button3=gtk_button_new_with_label("Apagar parque");
    g_signal_connect(button1, "clicked", G_CALLBACK(criar), NULL);
    g_signal_connect(button2,"clicked", G_CALLBACK(carregar), NULL);
    g_signal_connect(button3,"clicked", G_CALLBACK(apagar), NULL);

    GtkWidget *box; box = gtk_vbox_new(GTK_ORIENTATION_VERTICAL,20);
     gtk_box_pack_start(GTK_BOX(box),label1,FALSE,FALSE,0);
     gtk_box_pack_start(GTK_BOX(box),entry1,FALSE,FALSE,0);
     gtk_box_pack_start(GTK_BOX(box),label2,FALSE,FALSE,0);
     gtk_box_pack_start(GTK_BOX(box),entry2,FALSE,FALSE,0);
     gtk_box_pack_start(GTK_BOX(box),label3,FALSE,FALSE,0);
     gtk_box_pack_start(GTK_BOX(box),entry3,FALSE,FALSE,0);
     gtk_box_pack_start(GTK_BOX(box),label4,FALSE,FALSE,0);
     gtk_box_pack_start(GTK_BOX(box),entry4,FALSE,FALSE,0);
     gtk_box_pack_start(GTK_BOX(box),button1,FALSE,FALSE,0);
     gtk_box_pack_start(GTK_BOX(box),button2,FALSE,FALSE,0);
     gtk_box_pack_start(GTK_BOX(box),button3,FALSE,FALSE,0);

     gtk_container_add(GTK_CONTAINER(window),box);

     //GtkWidget *filechooserwidget = gtk_file_chooser_widget_new(GTK_FILE_CHOOSER_ACTION_OPEN);
     //gtk_container_add(GTK_CONTAINER(window), filechooserwidget);

     gtk_widget_show_all (window);

    printf("CRIAR PARQUE");
}

static void estacionar(GtkWidget *widget,gpointer data){
    if(Parque1.existe){
    GtkWidget *window,*button;
     window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
     gtk_window_set_title (GTK_WINDOW (window), "Estacionar veiculo");

    label1=gtk_label_new("Piso:");
    entry1=gtk_entry_new();
    label2=gtk_label_new("Linha:");
    entry2=gtk_entry_new();
    label3=gtk_label_new("Coluna:");
    entry3=gtk_entry_new();
    label4=gtk_label_new("Matricula:");
    entry4=gtk_entry_new();
    button1 = gtk_button_new_with_label("Estacionar");
    button2=gtk_button_new_with_label("Cancelar");
    g_signal_connect(button1, "clicked", G_CALLBACK(estacionar_carro), NULL);
    g_signal_connect(button2,"clicked", G_CALLBACK(cancelar), NULL);

    GtkWidget *box;
    box = gtk_vbox_new(GTK_ORIENTATION_VERTICAL,20);
     gtk_box_pack_start(GTK_BOX(box),label1,FALSE,FALSE,0);
     gtk_box_pack_start(GTK_BOX(box),entry1,FALSE,FALSE,0);
     gtk_box_pack_start(GTK_BOX(box),label2,FALSE,FALSE,0);
     gtk_box_pack_start(GTK_BOX(box),entry2,FALSE,FALSE,0);
     gtk_box_pack_start(GTK_BOX(box),label3,FALSE,FALSE,0);
     gtk_box_pack_start(GTK_BOX(box),entry3,FALSE,FALSE,0);
     gtk_box_pack_start(GTK_BOX(box),label4,FALSE,FALSE,0);
     gtk_box_pack_start(GTK_BOX(box),entry4,FALSE,FALSE,0);
     gtk_box_pack_start(GTK_BOX(box),button1,FALSE,FALSE,0);
     gtk_box_pack_start(GTK_BOX(box),button2,FALSE,FALSE,0);

     gtk_container_add(GTK_CONTAINER(window),box);
     gtk_widget_show_all (window);
     }
     else{
        GtkWidget *popup;
        popup=gtk_message_dialog_new(GTK_WINDOW(data),
                                     GTK_DIALOG_DESTROY_WITH_PARENT,
                                     GTK_MESSAGE_ERROR,
                                     GTK_BUTTONS_OK,
                                     "Ainda nao seleccionou um parque!");
      gtk_window_set_title(GTK_WINDOW(popup), "Information");
      gtk_dialog_run(GTK_DIALOG(popup));
      gtk_widget_destroy(popup);
     }

    printf("ESTACIONAR");
}

static void retirar(GtkWidget *widget,gpointer data){
    GtkWidget *window;//*button;
     window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
     gtk_window_set_title (GTK_WINDOW (window), "Retirar PARQUE");

    label4=gtk_label_new("Matricula:");
    entry4=gtk_entry_new();
    button1 = gtk_button_new_with_label("Retirar");
    button2=gtk_button_new_with_label("Cancelar");
    g_signal_connect(button1, "clicked", G_CALLBACK(retirar_carro), NULL);
    g_signal_connect(button2,"clicked", G_CALLBACK(cancelar), NULL);

    GtkWidget *box;
    box = gtk_vbox_new(GTK_ORIENTATION_VERTICAL,20);
     gtk_box_pack_start(GTK_BOX(box),label4,FALSE,FALSE,0);
     gtk_box_pack_start(GTK_BOX(box),entry4,FALSE,FALSE,0);
     gtk_box_pack_start(GTK_BOX(box),button1,FALSE,FALSE,0);
     gtk_box_pack_start(GTK_BOX(box),button2,FALSE,FALSE,0);

     gtk_container_add(GTK_CONTAINER(window),box);
     gtk_widget_show_all (window);

    //printf("RETIRAR");
}

int main (int argc, char *argv[])
{

gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Parque");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    g_signal_connect(window, "destroy", G_CALLBACK(destroy), NULL);

    GtkWidget *layout = gtk_layout_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(window), layout);

    img=gtk_image_new_from_file("C:\\Users\\Utilizador\\Desktop\\UM\\AED2\\ProjGUI\\mostrador.png");
    gtk_layout_put(GTK_LAYOUT(layout), img, 200, 200);
    label=gtk_label_new("Parquimetro");
    gtk_layout_put(GTK_LAYOUT(layout),label,10,10);
    button1 = gtk_button_new_with_label("Criar parque");
    gtk_layout_put(GTK_LAYOUT(layout), button1, 100, 120);
    g_signal_connect(button1, "clicked", G_CALLBACK(criarParque), NULL);
    button2 = gtk_button_new_with_label("Estacionar veiculo");
    gtk_layout_put(GTK_LAYOUT(layout), button2, 220, 50);
    g_signal_connect(button2, "clicked", G_CALLBACK(estacionar), NULL);
    button3 = gtk_button_new_with_label("Retirar veiculo");
    gtk_layout_put(GTK_LAYOUT(layout), button3, 80, 35);
    g_signal_connect(button3, "clicked", G_CALLBACK(retirar), NULL);
    button4 = gtk_button_new_with_label("Consultar parque");
    gtk_layout_put(GTK_LAYOUT(layout), button4, 60, 235);
    g_signal_connect(button4, "clicked", G_CALLBACK(mostrarParque), NULL);
    gtk_widget_show_all(window);

    tooltips=gtk_tooltips_new();
    gtk_tooltips_set_tip(GTK_TOOLTIPS (tooltips),button1,"Cria novo parque",
                         "Pode definir a dimensão ou carregar as definicoes através de um ficheiro");

    gtk_main();

    return 0;
}

void toString()
{
	int i,j,k,slivre=0;
	for(k=1;k<Parque1.pis+1;k++)
	{
		printf("PISO %d\n",k);
		for(i=1;i<Parque1.lin+1;i++)
		{
			for(j=1;j<Parque1.col+1;j++)
			{
				if(Parque1.Lugar1[k][i][j].estado == false){
					printf("|L|\t");
				}else{
					printf("|O|\t");
				}
				//printf("|%c|\t",Parque1.Lugar1[i*j*k].estado);
				if(Parque1.Lugar1[k][i][j].estado == false)
					slivre++;
			}
		printf("\n");
		}
	}
	int socupado=(Parque1.lin*Parque1.col*Parque1.pis)-slivre;
	printf("\nL=Livre\nO=Ocupado\nO parque tem %d lugares ocupados e %d lugares livres",socupado,slivre);

	if(socupado==0&&slivre==0)
        printf("\nAinda nao seleccionou nenhum parque, va a criar parque ou carregar parque para iniciar um parque.");
}

/*gtk_init(&argc, &argv);

    GtkWidget *aboutdialog = gtk_about_dialog_new();
    gtk_about_dialog_set_name(GTK_ABOUT_DIALOG(aboutdialog), "Learn GTK+");
    gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(aboutdialog), "1.0");
    gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(aboutdialog), "An introduction to using GTK+");
    gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(aboutdialog), "http://learngtk.org/");
    gtk_dialog_run(GTK_DIALOG(aboutdialog));
    gtk_widget_destroy(aboutdialog);

return 0;

GtkWidget *button = NULL;
  GtkWidget *win = NULL;
  GtkWidget *vbox = NULL;

  // Initialize GTK+
  g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, (GLogFunc) gtk_false, NULL);
  gtk_init (&argc, &argv);
  g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, g_log_default_handler, NULL);

  // Create the main window
  win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_container_set_border_width (GTK_CONTAINER (win), 12);
  gtk_window_set_title (GTK_WINDOW (win), "Estacionar veiculo");
  gtk_window_set_position (GTK_WINDOW (win), GTK_WIN_POS_CENTER);
  gtk_widget_realize (win);
  g_signal_connect (win, "destroy", gtk_main_quit, NULL);

  // Create a vertical box with buttons
  vbox = gtk_vbox_new (TRUE, 6);
  gtk_container_add (GTK_CONTAINER (win), vbox);

  button = gtk_button_new_from_stock (GTK_STOCK_DIALOG_INFO);
  g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (helloWorld), (gpointer) win);
  gtk_box_pack_start (GTK_BOX (vbox), button, TRUE, TRUE, 0);

  button = gtk_button_new_from_stock (GTK_STOCK_CLOSE);
  g_signal_connect (button, "clicked", gtk_main_quit, NULL);
  gtk_box_pack_start (GTK_BOX (vbox), button, TRUE, TRUE, 0);

  //gtk_button_set_label("Estacionar");
  // Enter the main loop

  gtk_main ();
  return 0;*/

