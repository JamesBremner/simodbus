#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace simodbus {

	/// <summary>
	/// Summary for DlgConfiger
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class DlgConfiger : public System::Windows::Forms::Form
	{
	public:
		DlgConfiger(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~DlgConfiger()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::RadioButton^  Master;
	public: System::Windows::Forms::RadioButton^  Slave;
	private: System::Windows::Forms::RadioButton^  SerialradioButton;
	public: System::Windows::Forms::RadioButton^  TCPradioButton;
	public: 
	protected: 






	private: System::Windows::Forms::Label^  label3;
	public: System::Windows::Forms::TextBox^  COMPort;

	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::DataGridView^  dataGridView1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Station;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Register;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Value;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  OK;



	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->Master = (gcnew System::Windows::Forms::RadioButton());
			this->Slave = (gcnew System::Windows::Forms::RadioButton());
			this->SerialradioButton = (gcnew System::Windows::Forms::RadioButton());
			this->TCPradioButton = (gcnew System::Windows::Forms::RadioButton());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->COMPort = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->Station = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Register = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Value = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->OK = (gcnew System::Windows::Forms::Button());
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// Master
			// 
			this->Master->AutoSize = true;
			this->Master->Location = System::Drawing::Point(98, 30);
			this->Master->Name = L"Master";
			this->Master->Size = System::Drawing::Size(57, 17);
			this->Master->TabIndex = 1;
			this->Master->TabStop = true;
			this->Master->Text = L"Master";
			this->Master->UseVisualStyleBackColor = true;
			// 
			// Slave
			// 
			this->Slave->AutoSize = true;
			this->Slave->Location = System::Drawing::Point(188, 30);
			this->Slave->Name = L"Slave";
			this->Slave->Size = System::Drawing::Size(52, 17);
			this->Slave->TabIndex = 2;
			this->Slave->TabStop = true;
			this->Slave->Text = L"Slave";
			this->Slave->UseVisualStyleBackColor = true;
			// 
			// SerialradioButton
			// 
			this->SerialradioButton->AutoSize = true;
			this->SerialradioButton->Location = System::Drawing::Point(86, 15);
			this->SerialradioButton->Name = L"SerialradioButton";
			this->SerialradioButton->Size = System::Drawing::Size(51, 17);
			this->SerialradioButton->TabIndex = 4;
			this->SerialradioButton->TabStop = true;
			this->SerialradioButton->Text = L"Serial";
			this->SerialradioButton->UseVisualStyleBackColor = true;
			this->SerialradioButton->CheckedChanged += gcnew System::EventHandler(this, &DlgConfiger::radioButton3_CheckedChanged);
			// 
			// TCPradioButton
			// 
			this->TCPradioButton->AutoSize = true;
			this->TCPradioButton->Location = System::Drawing::Point(98, 132);
			this->TCPradioButton->Name = L"TCPradioButton";
			this->TCPradioButton->Size = System::Drawing::Size(46, 17);
			this->TCPradioButton->TabIndex = 5;
			this->TCPradioButton->TabStop = true;
			this->TCPradioButton->Text = L"TCP";
			this->TCPradioButton->UseVisualStyleBackColor = true;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(188, 93);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(64, 13);
			this->label3->TabIndex = 6;
			this->label3->Text = L"COM PORT";
			// 
			// COMPort
			// 
			this->COMPort->Location = System::Drawing::Point(276, 93);
			this->COMPort->Name = L"COMPort";
			this->COMPort->Size = System::Drawing::Size(61, 20);
			this->COMPort->TabIndex = 7;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(188, 132);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(17, 13);
			this->label4->TabIndex = 8;
			this->label4->Text = L"IP";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(276, 132);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(157, 20);
			this->textBox2->TabIndex = 9;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->SerialradioButton);
			this->groupBox1->Location = System::Drawing::Point(12, 78);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(459, 97);
			this->groupBox1->TabIndex = 10;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Connection";
			// 
			// groupBox2
			// 
			this->groupBox2->Location = System::Drawing::Point(12, 12);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(459, 60);
			this->groupBox2->TabIndex = 11;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Simulate";
			// 
			// dataGridView1
			// 
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(3) {this->Station, 
				this->Register, this->Value});
			this->dataGridView1->Location = System::Drawing::Point(28, 223);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->Size = System::Drawing::Size(344, 269);
			this->dataGridView1->TabIndex = 12;
			// 
			// Station
			// 
			this->Station->HeaderText = L"Station";
			this->Station->Name = L"Station";
			// 
			// Register
			// 
			this->Register->HeaderText = L"Register";
			this->Register->Name = L"Register";
			// 
			// Value
			// 
			this->Value->HeaderText = L"Value";
			this->Value->Name = L"Value";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(434, 246);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(126, 23);
			this->button1->TabIndex = 13;
			this->button1->Text = L"Load from File";
			this->button1->UseVisualStyleBackColor = true;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(434, 312);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(126, 23);
			this->button2->TabIndex = 14;
			this->button2->Text = L"Save to File";
			this->button2->UseVisualStyleBackColor = true;
			// 
			// OK
			// 
			this->OK->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->OK->Location = System::Drawing::Point(494, 30);
			this->OK->Name = L"OK";
			this->OK->Size = System::Drawing::Size(75, 23);
			this->OK->TabIndex = 15;
			this->OK->Text = L"OK";
			this->OK->UseVisualStyleBackColor = true;
			// 
			// DlgConfiger
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(596, 545);
			this->Controls->Add(this->OK);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->COMPort);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->TCPradioButton);
			this->Controls->Add(this->Slave);
			this->Controls->Add(this->Master);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->groupBox2);
			this->Name = L"DlgConfiger";
			this->Text = L"Simodbus Configuration";
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void radioButton3_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 }
};
}
