#pragma once

namespace OpenGL {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for ToolWindow
	/// </summary>
	public ref class ToolWindow : public System::Windows::Forms::Form
	{
	public:
		static bool RenderRedChannel;
		static bool RenderGreenChannel;
		static bool RenderBlueChannel;

		ToolWindow(void)
		{
			InitializeComponent();
			RenderRedChannel = checkBox1->Checked;
			RenderGreenChannel = checkBox2->Checked;
			RenderBlueChannel = checkBox3->Checked;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ToolWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::CheckBox^ checkBox1;
	protected:
	private: System::Windows::Forms::CheckBox^ checkBox2;
	private: System::Windows::Forms::CheckBox^ checkBox3;

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
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox3 = (gcnew System::Windows::Forms::CheckBox());
			this->SuspendLayout();
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Checked = true;
			this->checkBox1->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox1->Location = System::Drawing::Point(12, 12);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(128, 24);
			this->checkBox1->TabIndex = 0;
			this->checkBox1->Text = L"Red Channel";
			this->checkBox1->UseVisualStyleBackColor = true;
			this->checkBox1->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::checkBox1_CheckedChanged);
			// 
			// checkBox2
			// 
			this->checkBox2->AutoSize = true;
			this->checkBox2->Location = System::Drawing::Point(12, 45);
			this->checkBox2->Name = L"checkBox2";
			this->checkBox2->Size = System::Drawing::Size(143, 24);
			this->checkBox2->TabIndex = 1;
			this->checkBox2->Text = L"Green Channel";
			this->checkBox2->UseVisualStyleBackColor = true;
			this->checkBox2->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::checkBox2_CheckedChanged);
			// 
			// checkBox3
			// 
			this->checkBox3->AutoSize = true;
			this->checkBox3->Location = System::Drawing::Point(10, 75);
			this->checkBox3->Name = L"checkBox3";
			this->checkBox3->Size = System::Drawing::Size(130, 24);
			this->checkBox3->TabIndex = 2;
			this->checkBox3->Text = L"Blue Channel";
			this->checkBox3->UseVisualStyleBackColor = true;
			this->checkBox3->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::checkBox3_CheckedChanged);
			// 
			// ToolWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(249, 269);
			this->Controls->Add(this->checkBox3);
			this->Controls->Add(this->checkBox2);
			this->Controls->Add(this->checkBox1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"ToolWindow";
			this->Text = L"ToolWindow";
			this->TopMost = true;
			this->Load += gcnew System::EventHandler(this, &ToolWindow::ToolWindow_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void ToolWindow_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void checkBox1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		RenderRedChannel = checkBox1->Checked;
	}
	private: System::Void checkBox2_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		RenderGreenChannel = checkBox2->Checked;
	}
	private: System::Void checkBox3_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		RenderBlueChannel = checkBox3->Checked;
	}
};
}
