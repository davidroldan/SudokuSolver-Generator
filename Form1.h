#pragma once
#include <fstream>
#include <string>
#include <ctime>

namespace practica3Ventana {
	//typedefs, constantes y variables globales (hay alguna variable global ya que no se pueden pasar por parametros a las funciones de Eventos)
	
	const int N = 9;

	typedef int tTablero[N][N];
	tTablero solucionGlobal;//variable global (solucionGlobal)

	typedef struct{ //Las casillas iniciales se veran con la propiedad textBox->Enabled.
		tTablero actual;
		tTablero regiones;
		int cont;
	} tSudoku;
	tSudoku sudoku = { //variable global (sudoku)
		{},
		{0,0,0,1,1,1,2,2,2,
		0,0,0,1,1,1,2,2,2,
		0,0,0,1,1,1,2,2,2,
		3,3,3,4,4,4,5,5,5,
		3,3,3,4,4,4,5,5,5,
		3,3,3,4,4,4,5,5,5,
		6,6,6,7,7,7,8,8,8,
		6,6,6,7,7,7,8,8,8,
		6,6,6,7,7,7,8,8,8}
	}; //Inicializo regiones.

	typedef struct{
		int elemento[N];
		int cont;
	} tPosibles;

	typedef struct{
		int fila[N];
		int col[N];
		int cont;
	} tCandidatos;

	typedef int tVectorElementos[N*N];
	typedef struct{
		tVectorElementos vector;
		int cont;
	} tVector;

	typedef enum {directo, inverso} tModo;

	//namespaces	
	using namespace std;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	array<array<TextBox^>^>^ casillas; //array de textBoxes de 2 dim.
	public:
		Form1(void)
		{
			InitializeComponent();
			casillas = gcnew array<array<TextBox^>^>(9);
			for(int i=0; i < casillas->Length; i++)
				casillas[i] = gcnew array<TextBox^>(9);
			// 
			// inicializacion
			//
			for(int i = 0; i < N; i++)
				for(int j = 0; j < N; j++){
					casillas[i][j] = (gcnew System::Windows::Forms::TextBox());
					this->casillas[i][j]->Location = System::Drawing::Point(15 + 25*j, 44 + 25*i);
					this->casillas[i][j]->Size = System::Drawing::Size(20, 20);
					this->casillas[i][j]->TabIndex = j + 9*i;
					this->casillas[i][j]->MaxLength = 1;
					this->casillas[i][j]->ForeColor = System::Drawing::Color::Black;
					this->casillas[i][j]->TextChanged += gcnew System::EventHandler(this,&Form1::casillas_TextChanged);
					this->casillas[i][j]->Click += gcnew System::EventHandler(this,&Form1::casillas_Click);
					this->Controls->Add(casillas[i][j]);
				}
			colorearCasillas();
			bloquearSudoku();
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	protected: 
	protected: 
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  archivoToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  mnNuevo;
	private: System::Windows::Forms::ToolStripMenuItem^  mnGenSudoku;
	private: System::Windows::Forms::ToolStripMenuItem^  mnCargarArchivo;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
	private: System::Windows::Forms::ToolStripMenuItem^  mnSalir;
	private: System::Windows::Forms::StatusStrip^  statusStrip1;
	private: System::Windows::Forms::ToolStripStatusLabel^  statusName;
	private: System::Windows::Forms::ToolStripMenuItem^  mnCargarRegiones;
	private: System::Windows::Forms::ToolStripMenuItem^  ayudaToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  mnAcercaDe;
	private: System::Windows::Forms::Label^  lblInfo;
	private: System::Windows::Forms::Button^  cbCompletarSimples;
	private: System::Windows::Forms::ToolStripMenuItem^  mnGuardar;
	private: System::Windows::Forms::Button^  cbInicializar;
	private: System::Windows::Forms::Button^  cbErrores;
	private: System::Windows::Forms::Button^  cbSolucion;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::Button^  cbPosicionUnica;
	private: System::Windows::Forms::ToolTip^  toolTip;

	private: System::ComponentModel::IContainer^  components;
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->archivoToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->mnNuevo = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->mnGenSudoku = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->mnCargarArchivo = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->mnCargarRegiones = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->mnGuardar = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->mnSalir = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ayudaToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->mnAcercaDe = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->statusName = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->lblInfo = (gcnew System::Windows::Forms::Label());
			this->cbCompletarSimples = (gcnew System::Windows::Forms::Button());
			this->cbInicializar = (gcnew System::Windows::Forms::Button());
			this->cbErrores = (gcnew System::Windows::Forms::Button());
			this->cbSolucion = (gcnew System::Windows::Forms::Button());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->cbPosicionUnica = (gcnew System::Windows::Forms::Button());
			this->toolTip = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->menuStrip1->SuspendLayout();
			this->statusStrip1->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->archivoToolStripMenuItem, 
				this->ayudaToolStripMenuItem});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(408, 24);
			this->menuStrip1->TabIndex = 1;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// archivoToolStripMenuItem
			// 
			this->archivoToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {this->mnNuevo, 
				this->mnCargarRegiones, this->mnGuardar, this->toolStripSeparator1, this->mnSalir});
			this->archivoToolStripMenuItem->Name = L"archivoToolStripMenuItem";
			this->archivoToolStripMenuItem->Size = System::Drawing::Size(60, 20);
			this->archivoToolStripMenuItem->Text = L"Archivo";
			// 
			// mnNuevo
			// 
			this->mnNuevo->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->mnGenSudoku, 
				this->mnCargarArchivo});
			this->mnNuevo->Name = L"mnNuevo";
			this->mnNuevo->Size = System::Drawing::Size(244, 22);
			this->mnNuevo->Text = L"Nueva Partida";
			// 
			// mnGenSudoku
			// 
			this->mnGenSudoku->Name = L"mnGenSudoku";
			this->mnGenSudoku->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::N));
			this->mnGenSudoku->Size = System::Drawing::Size(238, 22);
			this->mnGenSudoku->Text = L"Generar Sudoku";
			this->mnGenSudoku->Click += gcnew System::EventHandler(this, &Form1::mnGenSudoku_Click);
			// 
			// mnCargarArchivo
			// 
			this->mnCargarArchivo->Name = L"mnCargarArchivo";
			this->mnCargarArchivo->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::A));
			this->mnCargarArchivo->Size = System::Drawing::Size(238, 22);
			this->mnCargarArchivo->Text = L"Cargar desde Archivo...";
			this->mnCargarArchivo->Click += gcnew System::EventHandler(this, &Form1::mnCargarArchivo_Click);
			// 
			// mnCargarRegiones
			// 
			this->mnCargarRegiones->Name = L"mnCargarRegiones";
			this->mnCargarRegiones->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::R));
			this->mnCargarRegiones->Size = System::Drawing::Size(244, 22);
			this->mnCargarRegiones->Text = L"Cargar Regiones...";
			this->mnCargarRegiones->Click += gcnew System::EventHandler(this, &Form1::mnCargarRegiones_Click);
			// 
			// mnGuardar
			// 
			this->mnGuardar->Name = L"mnGuardar";
			this->mnGuardar->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::G));
			this->mnGuardar->Size = System::Drawing::Size(244, 22);
			this->mnGuardar->Text = L"Guardar Sudoku como...";
			this->mnGuardar->Click += gcnew System::EventHandler(this, &Form1::mnGuardar_Click);
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(241, 6);
			// 
			// mnSalir
			// 
			this->mnSalir->Name = L"mnSalir";
			this->mnSalir->Size = System::Drawing::Size(244, 22);
			this->mnSalir->Text = L"Salir";
			this->mnSalir->Click += gcnew System::EventHandler(this, &Form1::mnSalir_Click);
			// 
			// ayudaToolStripMenuItem
			// 
			this->ayudaToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->mnAcercaDe});
			this->ayudaToolStripMenuItem->Name = L"ayudaToolStripMenuItem";
			this->ayudaToolStripMenuItem->Size = System::Drawing::Size(53, 20);
			this->ayudaToolStripMenuItem->Text = L"Ayuda";
			// 
			// mnAcercaDe
			// 
			this->mnAcercaDe->Name = L"mnAcercaDe";
			this->mnAcercaDe->Size = System::Drawing::Size(193, 22);
			this->mnAcercaDe->Text = L"Acerca de Sudoku v2.0";
			this->mnAcercaDe->Click += gcnew System::EventHandler(this, &Form1::mnAcercaDe_Click);
			// 
			// statusStrip1
			// 
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->statusName});
			this->statusStrip1->Location = System::Drawing::Point(0, 295);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Size = System::Drawing::Size(408, 22);
			this->statusStrip1->TabIndex = 82;
			this->statusStrip1->Text = L"statusStrip1";
			// 
			// statusName
			// 
			this->statusName->Name = L"statusName";
			this->statusName->Size = System::Drawing::Size(175, 17);
			this->statusName->Text = L"No hay ningun Sudoku cargado";
			// 
			// lblInfo
			// 
			this->lblInfo->AutoSize = true;
			this->lblInfo->Location = System::Drawing::Point(12, 273);
			this->lblInfo->Name = L"lblInfo";
			this->lblInfo->Size = System::Drawing::Size(0, 13);
			this->lblInfo->TabIndex = 83;
			// 
			// cbCompletarSimples
			// 
			this->cbCompletarSimples->Location = System::Drawing::Point(5, 19);
			this->cbCompletarSimples->Name = L"cbCompletarSimples";
			this->cbCompletarSimples->Size = System::Drawing::Size(127, 27);
			this->cbCompletarSimples->TabIndex = 84;
			this->cbCompletarSimples->Text = L"Candidatos Unicos";
			this->toolTip->SetToolTip(this->cbCompletarSimples, L"Completa las casillas que tengan un solo candidato.");
			this->cbCompletarSimples->UseVisualStyleBackColor = true;
			this->cbCompletarSimples->Click += gcnew System::EventHandler(this, &Form1::cbCompletarSimples_Click);
			// 
			// cbInicializar
			// 
			this->cbInicializar->Location = System::Drawing::Point(6, 19);
			this->cbInicializar->Name = L"cbInicializar";
			this->cbInicializar->Size = System::Drawing::Size(127, 27);
			this->cbInicializar->TabIndex = 81;
			this->cbInicializar->Text = L"Limpiar Sudoku";
			this->toolTip->SetToolTip(this->cbInicializar, L"Borra todas las casillas completadas, dejando solo las casillas iniciales.");
			this->cbInicializar->UseVisualStyleBackColor = true;
			this->cbInicializar->Click += gcnew System::EventHandler(this, &Form1::cbInicializar_Click);
			// 
			// cbErrores
			// 
			this->cbErrores->Location = System::Drawing::Point(6, 52);
			this->cbErrores->Name = L"cbErrores";
			this->cbErrores->Size = System::Drawing::Size(127, 27);
			this->cbErrores->TabIndex = 82;
			this->cbErrores->Text = L"Mostrar Errores";
			this->toolTip->SetToolTip(this->cbErrores, L"Muestra las casillas erroneas en color rojo.");
			this->cbErrores->UseVisualStyleBackColor = true;
			this->cbErrores->Click += gcnew System::EventHandler(this, &Form1::cbErrores_Click);
			// 
			// cbSolucion
			// 
			this->cbSolucion->Location = System::Drawing::Point(6, 85);
			this->cbSolucion->Name = L"cbSolucion";
			this->cbSolucion->Size = System::Drawing::Size(127, 27);
			this->cbSolucion->TabIndex = 83;
			this->cbSolucion->Text = L"Solucion";
			this->toolTip->SetToolTip(this->cbSolucion, L"Completa el Sudoku entero, mostrando la solucion.");
			this->cbSolucion->UseVisualStyleBackColor = true;
			this->cbSolucion->Click += gcnew System::EventHandler(this, &Form1::cbSolucion_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->cbInicializar);
			this->groupBox1->Controls->Add(this->cbSolucion);
			this->groupBox1->Controls->Add(this->cbErrores);
			this->groupBox1->Location = System::Drawing::Point(257, 46);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(139, 118);
			this->groupBox1->TabIndex = 88;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Edición";
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->cbPosicionUnica);
			this->groupBox2->Controls->Add(this->cbCompletarSimples);
			this->groupBox2->Location = System::Drawing::Point(257, 170);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(138, 88);
			this->groupBox2->TabIndex = 89;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Completar";
			// 
			// cbPosicionUnica
			// 
			this->cbPosicionUnica->Location = System::Drawing::Point(5, 52);
			this->cbPosicionUnica->Name = L"cbPosicionUnica";
			this->cbPosicionUnica->Size = System::Drawing::Size(127, 27);
			this->cbPosicionUnica->TabIndex = 85;
			this->cbPosicionUnica->Text = L"Posiciones Unicas";
			this->toolTip->SetToolTip(this->cbPosicionUnica, L"Completa aquellos candidatos que solo aparezcan una vez en una fila, columna o re" 
				L"gion.");
			this->cbPosicionUnica->UseVisualStyleBackColor = true;
			this->cbPosicionUnica->Click += gcnew System::EventHandler(this, &Form1::cbPosicionUnica_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(408, 317);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->lblInfo);
			this->Controls->Add(this->statusStrip1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"Form1";
			this->Text = L"Sudoku v2.0";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->statusStrip1->ResumeLayout(false);
			this->statusStrip1->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox2->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

//Conversores de tipos

int textToInt(int i, int j){
	int num;
	if (this->casillas[i][j]->Text == L"1") num = 1;
	else if (this->casillas[i][j]->Text == L"2") num = 2;
	else if (this->casillas[i][j]->Text == L"3") num = 3;
	else if (this->casillas[i][j]->Text == L"4") num = 4;
	else if (this->casillas[i][j]->Text == L"5") num = 5;
	else if (this->casillas[i][j]->Text == L"6") num = 6;
	else if (this->casillas[i][j]->Text == L"7") num = 7;
	else if (this->casillas[i][j]->Text == L"8") num = 8;
	else if (this->casillas[i][j]->Text == L"9") num = 9;
	else if (this->casillas[i][j]->Text == L"") num = 0;
	else num = -1;
	return num;
}
void systemStringtoString ( String ^ s, string& os ) { //convierte de System::String a string
   using namespace Runtime::InteropServices;
   const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
   os = chars;
   Marshal::FreeHGlobal(IntPtr((void*)chars));
}

//Funciones relacionadas con la ventana grafica

void colorearCasillas(){ //colorea segun las regiones
	for (int i = 0; i < N; i++)
		for(int j = 0; j < N; j++){
			if (sudoku.regiones[i][j] == 0)
				this->casillas[i][j]->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)), 
				static_cast<System::Int32>(static_cast<System::Byte>(128)));
			else if (sudoku.regiones[i][j] == 1)
				this->casillas[i][j]->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(200)), 
				static_cast<System::Int32>(static_cast<System::Byte>(200)));
			else if (sudoku.regiones[i][j] == 2)
				this->casillas[i][j]->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(150)), static_cast<System::Int32>(static_cast<System::Byte>(255)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			else if (sudoku.regiones[i][j] == 3)
				this->casillas[i][j]->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(200)), static_cast<System::Int32>(static_cast<System::Byte>(255)), 
				static_cast<System::Int32>(static_cast<System::Byte>(200)));
			else if (sudoku.regiones[i][j] == 4)
				this->casillas[i][j]->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(200)), static_cast<System::Int32>(static_cast<System::Byte>(200)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			else if (sudoku.regiones[i][j] == 5)
				this->casillas[i][j]->BackColor = System::Drawing::Color::White;
			else if (sudoku.regiones[i][j] == 6)
				this->casillas[i][j]->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(200)), static_cast<System::Int32>(static_cast<System::Byte>(255)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			else if (sudoku.regiones[i][j] == 7)
				this->casillas[i][j]->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)), 
				static_cast<System::Int32>(static_cast<System::Byte>(200)));
			else if (sudoku.regiones[i][j] == 8)
				this->casillas[i][j]->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(200)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
		}


}
void bloqueoBotones(bool bloquear){
	this->cbInicializar->Enabled = bloquear;
	this->cbErrores->Enabled = bloquear;
	this->cbCompletarSimples->Enabled = bloquear;
	this->cbSolucion->Enabled = bloquear;
	this->cbPosicionUnica->Enabled = bloquear;
}

void bloquearSudoku(){
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++){
			this->casillas[i][j]->Enabled = false;
			sudoku.actual[i][j] = 0;
			this->casillas[i][j]->Text = L"";
		}
	bloqueoBotones(false);
}
bool buscarSeleccionFila(int &i, int &j){
	bool encontrado = false;
	i = 0;
	while ((i < N) && (!encontrado))
		if (this->casillas[i][j]->Focused)
			encontrado = true;
		else i++;
	return encontrado;
}
bool buscarSeleccion(int &i, int &j){
	bool encontrado = false;
	j = 0;
	while ((j < N) && (!encontrado))
		if (buscarSeleccionFila(i, j))
			encontrado = true;
		else j++;
	return encontrado;
}
void bloquearIniciales(){
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (sudoku.actual[i][j] == 0)
				casillas[i][j]->Enabled = true;
			else
				casillas[i][j]->Enabled = false;
}
void dibujarSudoku(){
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (sudoku.actual[i][j] != 0)
				this->casillas[i][j]->Text = Convert::ToString(sudoku.actual[i][j]);
			else this->casillas[i][j]->Text = L"";
}

//Funciones de cargado y guardado

bool cargarSudoku (string nombre, String ^ &tipoError){
	ifstream archivo;
	bool error = false;
	int fila, col;
	archivo.open(nombre);
	if (!archivo.is_open()){ //si no se abre el archivo
		error = true;
		tipoError = L"Error, no se ha podido abrir el archivo.";
	}
	else{ //si se abre el archivo
		archivo >> fila >> col; //Lee coordenadas de casilla
		if (((fila <= 0 ) || (col <= 0) || (fila > N) || (col > N)) && (fila != -1)){
			error = true;
			tipoError = L"Error, coordenada introducida fuera del intervalo [1..9].";
		}
		while ((!error) && (!archivo.fail())){
			archivo >> sudoku.actual[fila-1][col-1]; //Lee valor de casilla
			if ((sudoku.actual[fila-1][col-1] <= 0) || (sudoku.actual[fila-1][col-1] > N)){
				error = true;
				tipoError = L"Error, valor introducido fuera del intervalo [1..9].";
			}
			archivo >> fila >> col; //Lee coordenadas de casilla
			if (((fila <= 0 ) || (col <= 0) || (fila > N) || (col > N)) && (fila != -1)){
				error = true;
				tipoError = L"Error, coordenada introducida fuera del intervalo [1..9].";
			}
		}
	}
	archivo.close();
	return !error;
}
bool guardarSudoku(string nombre, String ^ &tipoError){
	ofstream archivo;
	bool error = false;
	archivo.open(nombre);
	if (!archivo.is_open()){ //si no se abre el archivo
		error = true;
		tipoError = L"Error, no se ha podido abrir el archivo. Puede que este siendo usado por otro proceso.";
	}
	else{ //si se abre el archivo
		for (int fila = 0; fila < N; fila++)
			for (int col = 0; col < N; col++)
				if (!this->casillas[fila][col]->Enabled)
					archivo << fila+1 << " " << col+1 << " " << sudoku.actual[fila][col] << endl;
	}
	return !error;
}
bool cargarRegiones (string nombre, String ^ &tipoError){
	//No se comprueban fallos en este archivo.
	ifstream archivo;
	bool error = false;
	archivo.open(nombre);
	if (!archivo.is_open()){
		error = true;
		tipoError =  "Error, no se ha podido abrir el archivo.";
	}
	else
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++){
				archivo >> sudoku.regiones[i][j];
				sudoku.regiones[i][j]--;
			}
	archivo.close();
	return !error;
}

//Funciones relacionadas con los tableros

void formatearTablero(tTablero mat1){
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
			mat1[i][j] = 0;
}
void formatearSudoku(){
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++){
			this->casillas[i][j]->Enabled = true;
			sudoku.actual[i][j] = 0;
			sudoku.cont = N*N;
			this->casillas[i][j]->Text = L"";
		}
}
void igualarTableros(tTablero mat1, tTablero mat2){
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			mat1[i][j] = mat2[i][j];
}
bool compararSudokuFila(tTablero mat1, tTablero mat2, int fila){
	bool iguales = true;
	int pos = 0;
	while ((pos < N) && (iguales))
		if (mat1[fila][pos] != mat2[fila][pos])
			iguales = false;
		else pos++;
	return iguales;

}
bool compararSudoku(tTablero mat1, tTablero mat2){
	bool iguales = true;
	int fila = 0;
	while ((fila < N) && (iguales)){
		iguales = compararSudokuFila(mat1, mat2, fila);
		fila++;
	}
	return iguales;
}
void inicializarSudoku(){
	sudoku.cont = N*N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (this->casillas[i][j]->Enabled) sudoku.actual[i][j] = 0;
			else sudoku.cont--;
	dibujarSudoku();
	this->lblInfo->Text = L"";
}
bool comprobarFila(tTablero matTablero, int fila, int num){
	bool numPosible = true;
	int pos = 0;
	while ((pos < N) && (numPosible))
		if (matTablero[fila][pos] == num)
			numPosible = false;
		else pos++;
	return numPosible;
}
bool comprobarCol(tTablero matTablero, int col, int num){
	bool numPosible = true;
	int pos = 0;
	while ((pos < N) && (numPosible))
		if (matTablero[pos][col] == num)
			numPosible = false;
		else pos++;
	return numPosible;
}
bool comprobarFilaDeRegion(tTablero matTablero, int col, int num, int i, int region){
	bool numPosible = true;
	int j = 0;
	while ((j < N) && (numPosible))
		if ((sudoku.regiones[i][j] == region) && (matTablero[i][j] == num))
			numPosible = false;
		else j++;
	return numPosible;
}
bool comprobarRegion(tTablero matTablero, int fila, int col, int num){
	bool numPosible = true;
	int i = 0, region = sudoku.regiones[fila][col];
	while ((i < N) && (numPosible))
		if (!comprobarFilaDeRegion(matTablero, col, num, i, region))
			numPosible = false;
		else i++;
	return numPosible;
}
bool comprobarNum(tTablero matTablero, int fila, int col, int num){
	bool posible = (comprobarRegion(matTablero, fila, col, num) &&
		comprobarFila(matTablero, fila, num) && comprobarCol(matTablero, col, num));
	return posible;
}
void comprobarPosibles(tTablero matTablero, int fila, int col, tPosibles &posibles){
	for (int num = 1; num <= N; num++)
			if (comprobarNum(matTablero, fila, col, num)){
				posibles.elemento[posibles.cont] = num;
				posibles.cont++;
			}
}
void comprobarCandidatosFila(tTablero matTablero, int fila, int num, tCandidatos &candidatos){
	for (int col = 0; col < N; col++)
			if (matTablero[fila][col] == 0 && comprobarNum(matTablero, fila, col, num)){
				candidatos.col[candidatos.cont] = col;
				candidatos.cont++;
			}
}
void comprobarCandidatosColumna(tTablero matTablero, int col, int num, tCandidatos &candidatos){
	for (int fila = 0; fila < N; fila++)
			if (matTablero[fila][col] == 0 && comprobarNum(matTablero, fila, col, num)){
				candidatos.fila[candidatos.cont] = fila;
				candidatos.cont++;
			}
}
void comprobarCandidatosRegion(tTablero matTablero, int region, int num, tCandidatos &candidatos){
	for (int fila = 0; fila < N; fila++)
		for (int col = 0; col < N; col++)
			if (matTablero[fila][col] == 0 && sudoku.regiones[fila][col] == region && comprobarNum(matTablero, fila, col, num)){
				candidatos.fila[candidatos.cont] = fila;
				candidatos.col[candidatos.cont] = col;
				candidatos.cont++;
			}
}
void completarCandidatosFila(tTablero matTableroAux, tTablero matTablero, int &numColocados){
	tCandidatos candidatos;
	for (int fila = 0; fila < N; fila++)
			for (int num = 1; num <= N; num++){
				candidatos.cont = 0;
				comprobarCandidatosFila(matTableroAux, fila, num, candidatos);
				if ((candidatos.cont == 1) && (matTablero[fila][candidatos.col[0]] == 0)){
					this->casillas[fila][candidatos.col[0]]->ForeColor = System::Drawing::Color::Black;
					matTablero[fila][candidatos.col[0]] = num;
					numColocados++;
				}
			}
}
void completarCandidatosColumna(tTablero matTableroAux, tTablero matTablero, int &numColocados){
	tCandidatos candidatos;
	for (int col = 0; col < N; col++)
			for (int num = 1; num <= N; num++){
				candidatos.cont = 0;
				comprobarCandidatosColumna(matTableroAux, col, num, candidatos);
				if ((candidatos.cont == 1) && (matTablero[candidatos.fila[0]][col] == 0)){
					this->casillas[candidatos.fila[0]][col]->ForeColor = System::Drawing::Color::Black;
					matTablero[candidatos.fila[0]][col] = num;
					numColocados++;
				}
			}
}
void completarCandidatosRegion(tTablero matTableroAux, tTablero matTablero, int &numColocados){
	tCandidatos candidatos;
	for (int region = 0; region < N; region++)
		for (int num = 1; num <= N; num++){
				candidatos.cont = 0;
				comprobarCandidatosRegion(matTableroAux, region, num, candidatos);
				if ((candidatos.cont == 1) && (matTablero[candidatos.fila[0]][candidatos.col[0]] == 0)){
					this->casillas[candidatos.fila[0]][candidatos.col[0]]->ForeColor = System::Drawing::Color::Black;
					matTablero[candidatos.fila[0]][candidatos.col[0]] = num;
					numColocados++;
				}
		}
}

//Funciones para crear la solucion del sudoku
/*int completarCandidatos(tTablero matTablero){
	tCandidatos candidatos;
	int numColocados = 0;
	for (int pos = 0; pos < N; pos++){
			for (int num = 1; num <= N; num++){
				candidatos.cont = 0;
				comprobarCandidatosFila(matTablero, pos, num, candidatos);
				if ((candidatos.cont == 1) && (matTablero[pos][candidatos.col[0]] == 0)){
					this->casillas[pos][candidatos.col[0]]->ForeColor = System::Drawing::Color::Black;
					matTablero[pos][candidatos.col[0]] = num;
					numColocados++;
				}
			}
			for (int num = 1; num <= N; num++){
				candidatos.cont = 0;
				comprobarCandidatosColumna(matTablero, pos, num, candidatos);
				if ((candidatos.cont == 1) && (matTablero[candidatos.fila[0]][pos] == 0)){
					matTablero[candidatos.fila[0]][pos] = num;
					numColocados++;
				}
			}
	}
	for (int region = 0; region < N; region++)
		for (int num = 1; num <= N; num++){
				candidatos.cont = 0;
				comprobarCandidatosRegion(matTablero, region, num, candidatos);
				if ((candidatos.cont == 1) && (matTablero[candidatos.fila[0]][candidatos.col[0]] == 0)){
					matTablero[candidatos.fila[0]][candidatos.col[0]] = num;
					numColocados++;
				}
		}
	return numColocados;	
}*/
int completarSimples(tTablero matTablero, bool &fallo){
	//No utiliza matriz auxiliar porque es subfuncion de resolver sudoku
	tPosibles posibles;
	int numColocados = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (matTablero[i][j] == 0){
				posibles.cont = 0;
				comprobarPosibles(matTablero, i, j, posibles);
				if (posibles.cont == 1){
					matTablero[i][j] = posibles.elemento[0];
					numColocados++;
				}
				else if (posibles.cont == 0) fallo = true;
			}		
	return numColocados;
}
bool sudokuCompletoFila(tTablero mat1, int fila){
	bool completo = true;
	int pos = 0;
	while ((pos < N) && (completo))
		if (mat1[fila][pos] == 0)
			completo = false;
		else pos++;
	return completo;

}
bool sudokuCompleto(tTablero mat1){
	bool completo = true;
	int fila = 0;
	while ((fila < N) && (completo)){
		completo = sudokuCompletoFila(mat1, fila);
		fila++;
	}
	return completo;
}
bool buscarHuecoFila(tTablero mat1, int &a, int &b, int i){
	bool encontrado = false;
	int j = 0;
	while ((j < N) && (!encontrado)){
		if (mat1[i][j] == 0){
			encontrado = true;
			a = i;
			b = j;
		}
		else j++;
	}
	return encontrado;
}
bool buscarHueco(tTablero mat1, int &a, int &b){//busca la primera casilla que no esta rellena en el sudoku
	int i = 0;
	bool encontrado = false;
	while ((i < N) && (!encontrado)){
		encontrado = buscarHuecoFila(mat1, a, b, i);	
		i++;
	}
	return encontrado;
}
bool resolverSudoku(tTablero matTablero, tModo modo){
	bool fallo = false, resuelto = false, recorrido = true, resolucionLogica = true;
	int numPosibles = 0, numSolucion = 0, a = 0, b = 0, n;
	int cont = completarSimples(matTablero, fallo);
	while (cont > 0 && !fallo) //metodo de resolucion por logica: (resolver casillas simples)
		cont = completarSimples(matTablero, fallo);
	if (!fallo && !sudokuCompleto(matTablero)){
		tTablero matAux;
		buscarHueco(matTablero, a, b);
		if (modo == directo) n = 1;
		else n = 9;
		recorrido = ((modo == directo) && (n <= 9)) || ((modo == inverso) && (n >= 1));
		while ((recorrido) && (!resuelto)){
			if (comprobarNum(matTablero, a, b, n)){
				igualarTableros(matAux, matTablero);
				matAux[a][b] = n;
				resuelto = resolverSudoku(matAux, modo); //metodo fuerza bruta: (probar un numero y ver si el sudoku tiene solucion)
			}
			if (modo == directo) n++;
			else n--;
			recorrido = ((modo == directo) && (n <= 9)) || ((modo == inverso) && (n >= 1));
		}
		if (resuelto) igualarTableros(matTablero, matAux);
		else fallo = true;
	}
	return !fallo;
}
bool comprobarSolUnica(tTablero mat1){ //Comprueba si un sudoku tiene sol. unica;
	tTablero matAux1, matAux2;
	bool unica;
	igualarTableros(matAux2, mat1);
	igualarTableros(matAux1, mat1);
	resolverSudoku(matAux1, directo); //Resolucion del sodoku por orden directo (si se aplica fuerza bruta, se aplica de 1 a 9)
	resolverSudoku(matAux2, inverso); //Resolucion del sodoku por orden directo (si se aplica fuerza bruta, se aplica de 9 a 1)
	unica = compararSudoku(matAux1, matAux2); //Si la solucion de los dos sudokus coincide es porque la solucion es unica
	return unica;
}
bool crearSolucion(String ^ &tipoError){
	igualarTableros(solucionGlobal, sudoku.actual);
	bool resoluble = resolverSudoku(solucionGlobal, directo);
	if (resoluble){
		if (!comprobarSolUnica(sudoku.actual)){
			resoluble = false;
			tipoError = L"El sudoku cargado no tiene solucion unica";
		}
	}
	else tipoError = L"El sudoku cargado no tiene solucion";
	return resoluble;
}

// Funciones de generar sudoku //

void generarPrimeraLinea(tTablero mat1){ //genera la primera fila del sudoku
	tVector vAux = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	int aux;
	for (int i = 0; i < N; i++)
		vAux.vector[i] = i+1;
	for (int j = 0; j < N; j++){
		aux = int((N-j) * rand()/ RAND_MAX);
		mat1[0][j] = vAux.vector[aux];
		for (int k = aux; k < N-1; k++)
			vAux.vector[k] = vAux.vector[k+1]; //desplazar vector a la izda para eliminar el valor obtenido
	}
}
int buscarValor(int valor, tVector v1){ //buscar un valor determinado en un vector
	int i = 0;
	while ((i < v1.cont) && (valor != v1.vector[i]))
		i++;
	return i;
}
void igualarVector(tVector &v1, tVector v2){
	for (int i = 0; i < N*N; i++)
		v1.vector[i] = v2.vector[i];
	v1.cont = v2.cont;
}
bool quitarNumeros(tTablero matSudoku, const int t1){ //crea un sudoku inicial a partir de una solucion de sudoku. Toma un nivel como parametro para determinar la dificultad.
	tVector vPosibles, vAux; //vectores auxiliares que guardaran los elementos del sudoku que no han sido eliminados y por tanto pueden eliminarse.
	tTablero matAux;
	const int limiteTiempo = 25000; //limite de tiempo = 25s.
	int numeros = N*N, aux, eliminar;
	bool eliminarNumero = false, imposible = false, limiteExcedido = false;
	for (int i = 0; i < N*N; i++) vPosibles.vector[i] = i; //inicializar vector a {0, 1, 2 .. N*N-1}
	for (int i = 0; i < N; i++){ //elimina N numeros, uno de cada fila (no hace falta hacer ninguna comprobacion para ello)
		aux = int(N * rand()/ RAND_MAX);
		matSudoku[i][aux] = 0;
		for (int k = aux + i*(N-1); k < N*N - 1; k++) vPosibles.vector[k] = vPosibles.vector[k+1]; //desplazar vector a la izda para eliminar el valor obtenido
	}
	vPosibles.cont = N*N - N; //como hay ya N numeros eliminados, el contador es el total menos N.
	igualarVector(vAux, vPosibles);
	eliminar = int(7 * rand()/ RAND_MAX) + 40; //num aleatorio entre 40 y 47 (sudokus entre 28 y 35 numeros)
	eliminar = 100;
	while ((eliminar > 0) && (!imposible) && (!limiteExcedido)){ //proceso de eliminar numeros segun el nivel que se escoja
		eliminarNumero = false;
		igualarVector(vAux, vPosibles);
		while ((!eliminarNumero) && (!imposible) && (!limiteExcedido)){
			igualarTableros(matAux, matSudoku); //inicializar matAux a matSudoku;
			aux = int(vAux.cont * rand()/ RAND_MAX);
			matAux[vAux.vector[aux] / N][vAux.vector[aux] % N] = 0; //Elimina un numero del sudoku
			if (comprobarSolUnica(matAux)){ //Si el sudoku tiene sol. unica (si el sudoku es valido)
				eliminarNumero = true;
				aux = buscarValor(vAux.vector[aux], vPosibles);
				for (int k = aux; k < vPosibles.cont - 1; k++)
					vPosibles.vector[k] = vPosibles.vector[k+1]; //desplazamiento a la izda desde la posicion k. Asi se elimina la posibilidad de escoger de nuevo el mismo numero.
				vPosibles.cont--; //Al eliminar un numero, el contador tambien se decrementa.
				igualarTableros(matSudoku, matAux);
				eliminar--;
			}
			else if (vAux.cont == 1) imposible = true; //si no se pueden quitar mas numeros, imposible = true y se sale del bucle.
			for (int k = aux; k < vAux.cont - 1; k++)
				vAux.vector[k] = vAux.vector[k+1]; //desplazamiento a la izda desde la posicion k. Evita bucles infinitos.
			vAux.cont--; //Al eliminar un numero, el contador tambien se decrementa.
			limiteExcedido = ((clock() - t1) > limiteTiempo); //limiteExcedido = (> 25 seg)
		}
	}
	return !limiteExcedido;
}

// Funciones Evento

private: System::Void mnSalir_Click(System::Object^  sender, System::EventArgs^  e){
			 this->Close();
		 }	
private: System::Void mnGenSudoku_Click(System::Object^  sender, System::EventArgs^  e){
			this->statusName->Text = L"Generando sudoku...";
			srand((unsigned)time(0));
			int t1 = clock();
			formatearTablero(solucionGlobal);
			generarPrimeraLinea(solucionGlobal);
			tModo modo = tModo(int(2 * rand()/ RAND_MAX)); //aleatorio entre directo o inverso (50%)
			resolverSudoku(solucionGlobal, modo);
			igualarTableros(sudoku.actual, solucionGlobal);
			if (quitarNumeros(sudoku.actual, t1)){
				bloquearIniciales();
				inicializarSudoku();
				bloqueoBotones(true);
				this->statusName->Text = L"Sudoku generado correctamente";
			}else{
				MessageBox::Show(L"No se ha podido generar el sudoku. Limite de tiempo excedido.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				bloquearSudoku();
				this->statusName->Text = L"No hay ningun Sudoku cargado";
			}
		 }
private: System::Void mnCargarArchivo_Click(System::Object^  sender, System::EventArgs^  e){
			string nombre;
			String ^ tipoError = gcnew String("");
			OpenFileDialog^ dialogo = gcnew OpenFileDialog; //abrir explorador de archivos
			dialogo->Filter = "Archivo de Sudoku (*.txt)|*.txt|Todos los archivos (*.*)|*.*";
			dialogo->FilterIndex = 1;
			dialogo->RestoreDirectory = true;
			if ( dialogo->ShowDialog() == System::Windows::Forms::DialogResult::OK ){//si se ha seleccionado el archivo
				systemStringtoString(dialogo->FileName, nombre);
				formatearSudoku();
				if (cargarSudoku(nombre, tipoError)){
					if (crearSolucion(tipoError)){
						bloquearIniciales();
						inicializarSudoku();
						bloqueoBotones(true);
						this->statusName->Text = L"Sudoku cargado correctamente";
					}
					else{
						MessageBox::Show(tipoError, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
						bloquearSudoku();
						this->statusName->Text = L"No hay ningun Sudoku cargado";
					}
				}
				else{
					MessageBox::Show(tipoError, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
					bloquearSudoku();
					this->statusName->Text = L"No hay ningun Sudoku cargado";
				}
			}
			   
		 }
private: System::Void mnGuardar_Click(System::Object^  sender, System::EventArgs^  e) {
			if (this->statusName->Text == L"No hay ningun Sudoku cargado")
				MessageBox::Show("No hay ningun sudoku cargado.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			else{
				string nombre;
				String ^ tipoError = gcnew String("");
				SaveFileDialog^ dialogo = gcnew SaveFileDialog; //abrir explorador de archivos
				dialogo->Filter = "Archivo de Sudoku (*.txt)|*.txt|Todos los archivos (*.*)|*.*";
				dialogo->FilterIndex = 1;
				dialogo->RestoreDirectory = true;
				if ( dialogo->ShowDialog() == System::Windows::Forms::DialogResult::OK ){
					systemStringtoString(dialogo->FileName, nombre);
					if (!guardarSudoku(nombre, tipoError))
						MessageBox::Show(tipoError, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
			}
		 }
private: System::Void mnCargarRegiones_Click(System::Object^  sender, System::EventArgs^  e){
			bool continuar = false;
			if (this->statusName->Text == L"No hay ningun Sudoku cargado") continuar = true;
			else if(MessageBox::Show("Se borrara el sudoku actual. ¿Desea continuar?", "Cargar regiones", MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes)
				continuar = true;
			if (continuar){
				this->statusName->Text = L"No hay ningun Sudoku cargado";
				bloquearSudoku();
				string nombre;
				String ^ tipoError = gcnew String("");
				OpenFileDialog^ dialogo = gcnew OpenFileDialog; //abrir explorador de archivos
				dialogo->Filter = "Archivo de Regiones (*.txt)|*.txt|Todos los archivos (*.*)|*.*";
				dialogo->FilterIndex = 1;
				dialogo->RestoreDirectory = true;
				if ( dialogo->ShowDialog() == System::Windows::Forms::DialogResult::OK ){//si se ha seleccionado el archivo
					tTablero regionesAux;
					igualarTableros(regionesAux, sudoku.regiones); //Guardar region actual por si hay error
					systemStringtoString(dialogo->FileName, nombre);
					formatearSudoku();
					if (cargarRegiones(nombre, tipoError))//funcion de carga de las regiones.
						colorearCasillas();
					else{
						MessageBox::Show(tipoError, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
						igualarTableros(sudoku.regiones, regionesAux); //Cargar regiones anteriores
					}
				}
			   
			 }
		}
private: System::Void mnAcercaDe_Click(System::Object^  sender, System::EventArgs^  e) {
			 MessageBox::Show("Sudoku v2.0 (Practica 3 Opcional) de David Roldan Santos.", "Sudoku v2.0", MessageBoxButtons::OK, MessageBoxIcon::Information);
		 }
private: System::Void casillas_TextChanged(System::Object^  sender, System::EventArgs^  e){
			 int aux, i, j;
			 if (buscarSeleccion(i,j)){//si hay un textBox seleccionado				
				aux = textToInt(i, j);
				if (aux == -1) this->lblInfo->Text = L"Valor incorrecto";
				else if (sudoku.actual[i][j] != 0 && aux == 0){
					this->casillas[i][j]->ForeColor = System::Drawing::Color::Black;
					sudoku.actual[i][j] = 0;
					sudoku.cont++;
					this->lblInfo->Text = L"";
				}
				else if (sudoku.actual[i][j] != aux)
					if (comprobarNum(sudoku.actual, i, j, aux)){
						if (sudoku.actual[i][j] == 0) sudoku.cont--;
						this->casillas[i][j]->ForeColor = System::Drawing::Color::Black;
						sudoku.actual[i][j] = aux;
						if (sudoku.cont == 0)
							this->lblInfo->Text = L"Sudoku completo.";
						else
							this->lblInfo->Text = L"";
					}else this->lblInfo->Text = L"Valor ya introducido en fila, columna o region.";
			}
			dibujarSudoku();
		}
private: System::Void casillas_Click(System::Object^  sender, System::EventArgs^  e){
			 int i, j;
			 buscarSeleccion(i, j);
			 if (sudoku.actual[i][j] == 0){
				String ^ texto = gcnew String("");
				texto = String::Concat(L"Candidatos para la casilla [", Convert::ToString(i+1), L"][", Convert::ToString(j+1), L"]: ");
				tPosibles posibles;
				posibles.cont = 0;
				comprobarPosibles(sudoku.actual, i, j, posibles);
				for (int k = 0; k < posibles.cont; k++)
					texto = String::Concat(texto, Convert::ToString(posibles.elemento[k]), L", ");
				this->lblInfo->Text = texto;
			 }
		 }
private: System::Void cbInicializar_Click(System::Object^  sender, System::EventArgs^  e){
			 inicializarSudoku();
			 this->lblInfo->Text = L"";
		 }
private: System::Void cbCompletarSimples_Click(System::Object^  sender, System::EventArgs^  e) {
				tTablero aux;
				tPosibles posibles;
				int numColocados = 0;
				igualarTableros(aux, sudoku.actual);
				for (int i = 0; i < N; i++)
					for (int j = 0; j < N; j++)
						if (sudoku.actual[i][j] == 0){
							posibles.cont = 0;
							comprobarPosibles(aux, i, j, posibles);
							if (posibles.cont == 1){
								this->casillas[i][j]->ForeColor = System::Drawing::Color::Black;
								sudoku.actual[i][j] = posibles.elemento[0];
								numColocados++;
							}
						}
				sudoku.cont -= numColocados;
				dibujarSudoku();
				if (sudoku.cont == 0) lblInfo->Text = L"Sudoku completo.";
				else lblInfo->Text = String::Concat(L"Casillas simples completadas: ", Convert::ToString(numColocados));
			}
private: System::Void cbPosicionUnica_Click(System::Object^  sender, System::EventArgs^  e) {
			tTablero aux;
			int numColocados = 0;
			igualarTableros(aux, sudoku.actual);
			completarCandidatosFila(aux, sudoku.actual, numColocados);
			completarCandidatosColumna(aux, sudoku.actual, numColocados);
			completarCandidatosRegion(aux, sudoku.actual, numColocados);
			sudoku.cont -= numColocados;
			dibujarSudoku();
			if (sudoku.cont == 0) lblInfo->Text = L"Sudoku completo.";
			else lblInfo->Text = String::Concat(L"Candidatos únicos completados: ", Convert::ToString(numColocados));
		}
			

private: System::Void cbSolucion_Click(System::Object^  sender, System::EventArgs^  e) {
			 igualarTableros(sudoku.actual, solucionGlobal);
			 for (int i = 0; i < N; i++)
					for (int j = 0; j < N; j++)
						this->casillas[i][j]->ForeColor = System::Drawing::Color::Black;
			 dibujarSudoku();
			 sudoku.cont = 0;
			 lblInfo->Text = L"Sudoku completo.";
		 }
private: System::Void cbErrores_Click(System::Object^  sender, System::EventArgs^  e){
			 for (int i = 0; i < N; i++)
				for (int j = 0; j < N; j++)
					if ((sudoku.actual[i][j] != 0) && (solucionGlobal[i][j] != sudoku.actual[i][j]))
						casillas[i][j]->ForeColor = System::Drawing::Color::Red;
		 }
};
}