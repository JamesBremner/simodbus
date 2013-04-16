#pragma once

/**

 @mainpage  SIMODBUS

 A modbus master/slave simulator

*/



#include "DlgConfiger.h"

#define OK 0

namespace simodbus {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// Main window
	///
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:

		

		Form1(void)
		{
			InitializeComponent();
			
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





	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  Station;

	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  Register;

	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Button^  Read;

	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::TextBox^  Value;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::StatusStrip^  statusStrip;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel1;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::Button^  RUN;
	private: System::Windows::Forms::RadioButton^  rbSTATIONS;


	private: System::Windows::Forms::RadioButton^  rbMASTER;

	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Label^  label5;
	public: System::Windows::Forms::TextBox^  COMPort;
	private: 
	private: System::Windows::Forms::Label^  label6;
	public: System::Windows::Forms::RadioButton^  rbTCP;
	private: 
	public: 

	private: 
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::RadioButton^  rbSERIAL;

	public: 

	private: System::Windows::Forms::DataGridView^  dataGridView1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn2;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn3;
	private: System::Windows::Forms::GroupBox^  groupBox4;
	private: System::Windows::Forms::RadioButton^  rbRTU;
	private: System::Windows::Forms::RadioButton^  rbASCII;
	private: System::Windows::Forms::RichTextBox^  logWindow;

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
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->Station = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->Register = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->Read = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->Value = (gcnew System::Windows::Forms::TextBox());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->statusStrip = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStripStatusLabel1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->RUN = (gcnew System::Windows::Forms::Button());
			this->rbSTATIONS = (gcnew System::Windows::Forms::RadioButton());
			this->rbMASTER = (gcnew System::Windows::Forms::RadioButton());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->COMPort = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->rbTCP = (gcnew System::Windows::Forms::RadioButton());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->rbSERIAL = (gcnew System::Windows::Forms::RadioButton());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->dataGridViewTextBoxColumn1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->rbRTU = (gcnew System::Windows::Forms::RadioButton());
			this->rbASCII = (gcnew System::Windows::Forms::RadioButton());
			this->logWindow = (gcnew System::Windows::Forms::RichTextBox());
			this->statusStrip->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->BeginInit();
			this->groupBox4->SuspendLayout();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(362, 121);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(25, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Log";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(21, 33);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(40, 13);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Station";
			// 
			// Station
			// 
			this->Station->Location = System::Drawing::Point(85, 150);
			this->Station->Name = L"Station";
			this->Station->Size = System::Drawing::Size(58, 20);
			this->Station->TabIndex = 4;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(21, 70);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(46, 13);
			this->label3->TabIndex = 5;
			this->label3->Text = L"Register";
			// 
			// Register
			// 
			this->Register->Location = System::Drawing::Point(85, 187);
			this->Register->Name = L"Register";
			this->Register->Size = System::Drawing::Size(58, 20);
			this->Register->TabIndex = 6;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(248, 33);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(40, 13);
			this->label4->TabIndex = 7;
			this->label4->Text = L"Value: ";
			// 
			// Read
			// 
			this->Read->Location = System::Drawing::Point(146, 31);
			this->Read->Name = L"Read";
			this->Read->Size = System::Drawing::Size(75, 23);
			this->Read->TabIndex = 8;
			this->Read->Text = L"READ";
			this->Read->UseVisualStyleBackColor = true;
			this->Read->Click += gcnew System::EventHandler(this, &Form1::Read_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(146, 68);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 9;
			this->button2->Text = L"WRITE";
			this->button2->UseVisualStyleBackColor = true;
			// 
			// Value
			// 
			this->Value->Location = System::Drawing::Point(251, 49);
			this->Value->Name = L"Value";
			this->Value->Size = System::Drawing::Size(69, 20);
			this->Value->TabIndex = 10;
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// statusStrip
			// 
			this->statusStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->toolStripStatusLabel1});
			this->statusStrip->Location = System::Drawing::Point(0, 480);
			this->statusStrip->Name = L"statusStrip";
			this->statusStrip->Size = System::Drawing::Size(672, 22);
			this->statusStrip->TabIndex = 11;
			this->statusStrip->Text = L"statusStrip1";
			// 
			// toolStripStatusLabel1
			// 
			this->toolStripStatusLabel1->Name = L"toolStripStatusLabel1";
			this->toolStripStatusLabel1->Size = System::Drawing::Size(16, 17);
			this->toolStripStatusLabel1->Text = L"   ";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Controls->Add(this->Value);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->label4);
			this->groupBox1->Controls->Add(this->button2);
			this->groupBox1->Controls->Add(this->Read);
			this->groupBox1->Location = System::Drawing::Point(12, 117);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(344, 100);
			this->groupBox1->TabIndex = 12;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Master Query";
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->RUN);
			this->groupBox2->Controls->Add(this->rbSTATIONS);
			this->groupBox2->Controls->Add(this->rbMASTER);
			this->groupBox2->Location = System::Drawing::Point(12, 28);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(200, 83);
			this->groupBox2->TabIndex = 13;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Simulate";
			// 
			// RUN
			// 
			this->RUN->Location = System::Drawing::Point(56, 43);
			this->RUN->Name = L"RUN";
			this->RUN->Size = System::Drawing::Size(75, 23);
			this->RUN->TabIndex = 2;
			this->RUN->Text = L"RUN";
			this->RUN->UseVisualStyleBackColor = true;
			this->RUN->Click += gcnew System::EventHandler(this, &Form1::RUN_Click);
			// 
			// rbSTATIONS
			// 
			this->rbSTATIONS->AutoSize = true;
			this->rbSTATIONS->Location = System::Drawing::Point(88, 20);
			this->rbSTATIONS->Name = L"rbSTATIONS";
			this->rbSTATIONS->Size = System::Drawing::Size(63, 17);
			this->rbSTATIONS->TabIndex = 1;
			this->rbSTATIONS->TabStop = true;
			this->rbSTATIONS->Text = L"Stations";
			this->rbSTATIONS->UseVisualStyleBackColor = true;
			// 
			// rbMASTER
			// 
			this->rbMASTER->AutoSize = true;
			this->rbMASTER->Location = System::Drawing::Point(24, 20);
			this->rbMASTER->Name = L"rbMASTER";
			this->rbMASTER->Size = System::Drawing::Size(57, 17);
			this->rbMASTER->TabIndex = 0;
			this->rbMASTER->TabStop = true;
			this->rbMASTER->Text = L"Master";
			this->rbMASTER->UseVisualStyleBackColor = true;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(166, 52);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(140, 20);
			this->textBox2->TabIndex = 15;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(121, 56);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(17, 13);
			this->label5->TabIndex = 14;
			this->label5->Text = L"IP";
			// 
			// COMPort
			// 
			this->COMPort->Location = System::Drawing::Point(166, 24);
			this->COMPort->Name = L"COMPort";
			this->COMPort->Size = System::Drawing::Size(44, 20);
			this->COMPort->TabIndex = 13;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(116, 25);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(37, 13);
			this->label6->TabIndex = 12;
			this->label6->Text = L"PORT";
			// 
			// rbTCP
			// 
			this->rbTCP->AutoSize = true;
			this->rbTCP->Location = System::Drawing::Point(26, 52);
			this->rbTCP->Name = L"rbTCP";
			this->rbTCP->Size = System::Drawing::Size(46, 17);
			this->rbTCP->TabIndex = 11;
			this->rbTCP->Text = L"TCP";
			this->rbTCP->UseVisualStyleBackColor = true;
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->textBox2);
			this->groupBox3->Controls->Add(this->COMPort);
			this->groupBox3->Controls->Add(this->rbSERIAL);
			this->groupBox3->Controls->Add(this->label5);
			this->groupBox3->Controls->Add(this->label6);
			this->groupBox3->Controls->Add(this->rbTCP);
			this->groupBox3->Location = System::Drawing::Point(218, 28);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(326, 83);
			this->groupBox3->TabIndex = 16;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Connection";
			// 
			// rbSERIAL
			// 
			this->rbSERIAL->AutoSize = true;
			this->rbSERIAL->Checked = true;
			this->rbSERIAL->Location = System::Drawing::Point(26, 25);
			this->rbSERIAL->Name = L"rbSERIAL";
			this->rbSERIAL->Size = System::Drawing::Size(51, 17);
			this->rbSERIAL->TabIndex = 4;
			this->rbSERIAL->TabStop = true;
			this->rbSERIAL->Text = L"Serial";
			this->rbSERIAL->UseVisualStyleBackColor = true;
			// 
			// dataGridView1
			// 
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(3) {this->dataGridViewTextBoxColumn1, 
				this->dataGridViewTextBoxColumn2, this->dataGridViewTextBoxColumn3});
			this->dataGridView1->Location = System::Drawing::Point(12, 221);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->Size = System::Drawing::Size(344, 247);
			this->dataGridView1->TabIndex = 17;
			// 
			// dataGridViewTextBoxColumn1
			// 
			this->dataGridViewTextBoxColumn1->HeaderText = L"Station";
			this->dataGridViewTextBoxColumn1->Name = L"dataGridViewTextBoxColumn1";
			// 
			// dataGridViewTextBoxColumn2
			// 
			this->dataGridViewTextBoxColumn2->HeaderText = L"Register";
			this->dataGridViewTextBoxColumn2->Name = L"dataGridViewTextBoxColumn2";
			// 
			// dataGridViewTextBoxColumn3
			// 
			this->dataGridViewTextBoxColumn3->HeaderText = L"Value";
			this->dataGridViewTextBoxColumn3->Name = L"dataGridViewTextBoxColumn3";
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->rbRTU);
			this->groupBox4->Controls->Add(this->rbASCII);
			this->groupBox4->Location = System::Drawing::Point(550, 28);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(110, 83);
			this->groupBox4->TabIndex = 18;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Mode";
			// 
			// rbRTU
			// 
			this->rbRTU->AutoSize = true;
			this->rbRTU->Checked = true;
			this->rbRTU->Location = System::Drawing::Point(21, 49);
			this->rbRTU->Name = L"rbRTU";
			this->rbRTU->Size = System::Drawing::Size(48, 17);
			this->rbRTU->TabIndex = 1;
			this->rbRTU->TabStop = true;
			this->rbRTU->Text = L"RTU";
			this->rbRTU->UseVisualStyleBackColor = true;
			// 
			// rbASCII
			// 
			this->rbASCII->AutoSize = true;
			this->rbASCII->Location = System::Drawing::Point(21, 22);
			this->rbASCII->Name = L"rbASCII";
			this->rbASCII->Size = System::Drawing::Size(52, 17);
			this->rbASCII->TabIndex = 0;
			this->rbASCII->Text = L"ASCII";
			this->rbASCII->UseVisualStyleBackColor = true;
			// 
			// logWindow
			// 
			this->logWindow->Location = System::Drawing::Point(362, 137);
			this->logWindow->Name = L"logWindow";
			this->logWindow->Size = System::Drawing::Size(298, 331);
			this->logWindow->TabIndex = 19;
			this->logWindow->Text = L"";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(672, 502);
			this->Controls->Add(this->logWindow);
			this->Controls->Add(this->groupBox4);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->statusStrip);
			this->Controls->Add(this->Register);
			this->Controls->Add(this->Station);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->groupBox1);
			this->Name = L"Form1";
			this->Text = L"SIMODBUS";
			this->statusStrip->ResumeLayout(false);
			this->statusStrip->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->EndInit();
			this->groupBox4->ResumeLayout(false);
			this->groupBox4->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void editToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 DlgConfiger^ dlg = gcnew DlgConfiger;
				 dlg->ShowDialog();

				 //if( dlg->TCPradioButton->Checked )
					// theModBusConnection.flagTCP = true;
				 //else {
					// theModBusConnection.flagTCP = false;
					// int p = -1;
					// Int32::TryParse( dlg->COMPort->Text, p );
					// theModBusConnection.setCOMPort( p );
				 //}

				 if( dlg->Slave->Checked ) {
					 // we want to simulate the slaves
					 this->Text = "Simodbus ( Slave )";
					 if( theModBusSim.Slave() ) {
						toolStripStatusLabel1->Text = "Failed to start station simulator";
						 return;
					 }
					 //if( ! theModBusConnection.flagTCP ) {
						// // start timer for serial slave server
						// timer1->Interval = 1000;
						// timer1->Enabled = true;
						// toolStripStatusLabel1->Text = "Serial station simulator running";
					 //}

				 } else {
					 // master simulation
					 this->Text = "Simodbus ( Master )";

					 theModBusSim.Connect();
				 }
			 }
			 /**

			 User has requested a register read

			 */
	private: System::Void Read_Click(System::Object^  sender, System::EventArgs^  e) {

				 theModBusSim.SendQueryRead(
					 Convert::ToInt32(Station->Text),
					 Convert::ToInt32(Register->Text) );
				 DisplayMessageAndReply();
				 Value->Text = theModBusSim.getValue().ToString();


				 array<String^>^ row = gcnew array<String^>(3);
				 row[0] = Station->Text;
				 row[1] = Register->Text;
				 row[2] = Value->Text;
				 dataGridView1->Rows->Add( row );

			 }
/**

  Time for slave simulator to check for input from master

*/
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {

			 int ret = theModBusSim.Poll();
			 if( ret == 1 || ret == 2 ) {
				 // there was no message
				 return;
			 }
			 DisplayMessageAndReply();

		 }
		 /**

		 User requested simulation start

		 */
private: System::Void RUN_Click(System::Object^  sender, System::EventArgs^  e) {

			 // check configuration
			 if( rbSTATIONS->Checked ) {
			 } else if ( rbMASTER->Checked ) {
			 } else {
				 toolStripStatusLabel1->Text = "Please select master or stations simulator";
				 return;
			 }
			 if( rbSERIAL->Checked ) {
				 theModBusSim.setSerial();
				 int p = -1;
				 Int32::TryParse( COMPort->Text, p );
				 theModBusSim.setCOMPort( p );
			 } else if ( rbTCP->Checked ) {
				 theModBusSim.setTCP();
			 } else {
				 toolStripStatusLabel1->Text = "Please select TCP or Serial";
				 return;
			 }
			 if( rbRTU->Checked ) {
				theModBusSim.setRTU();
			 } else {
				 theModBusSim.setASCII();
			 }

			 // Attempt connection
			 if( theModBusSim.Connect() != OK ) {
				 toolStripStatusLabel1->Text = "Connection Failed" + gcnew String(theModBusSim.GetLastError());
				 return;
			 }
			 // success
			 if( rbSTATIONS->Checked ) {
				 this->Text = "Simodbus ( Stations )";
			 } else if ( rbMASTER->Checked ) {
				 this->Text = "Simodbus ( Master )";
			 }
			 RUN->Enabled			= false;
			 rbSTATIONS->Enabled	= false;
			 rbMASTER->Enabled		= false;

			 if( rbSTATIONS->Checked ) {
				 if( theModBusSim.IsSerial() ) {
					 // start timer for serial slave server
					 timer1->Interval = 1000;
					 timer1->Enabled = true;
					 toolStripStatusLabel1->Text = "Serial station simulator running";
				 }
			 }

		 }
public:

	void DisplayMessageAndReply(void)
	{
		int start = logWindow->Text->Length;
		logWindow->AppendText( gcnew String( theModBusSim.getMessageSent().c_str() ) );
		logWindow->SelectionStart = start;
		logWindow->SelectionLength = logWindow->Text->Length - start - 1;
		logWindow->SelectionColor  = Color::Green;
		start = logWindow->Text->Length;
		logWindow->AppendText( gcnew String( theModBusSim.getReply().c_str() ) );
		logWindow->SelectionStart = start;
		logWindow->SelectionLength = logWindow->Text->Length - start - 1;
		logWindow->SelectionColor  = Color::Red;
	}
};
}

