/****************************************************************************************************************
* IN628 Programming 4
* Assignment 1 - Roguelike Game
* Dungeon Adventure!
* Created by Michael Inglis
* Written in C++/CLI Using Visual Studio 2013
* 
*******************************************************************************************************************/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//GameManager.h
// Game Manager Header File
// Created by : Michael Inglis
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "TileList.h"
#include "Tilemap.h"
#include "GameManager.h"

//define constants
#define CANVASWIDTH 1024
#define CANVASHEIGHT 720

namespace RoguelikeAssignment1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
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
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::Label^  scorelbl;


	private: System::Windows::Forms::Label^  hplbl;
	private: System::Windows::Forms::Label^  scoreValue;
	private: System::Windows::Forms::Label^  hpValue;
	private: System::Windows::Forms::Label^  feedbackLabel;
	private: System::Windows::Forms::Label^  explbl;
	private: System::Windows::Forms::Label^  expValue;









	protected:
	private: System::ComponentModel::IContainer^  components;

	protected:

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
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->scorelbl = (gcnew System::Windows::Forms::Label());
			this->hplbl = (gcnew System::Windows::Forms::Label());
			this->scoreValue = (gcnew System::Windows::Forms::Label());
			this->hpValue = (gcnew System::Windows::Forms::Label());
			this->feedbackLabel = (gcnew System::Windows::Forms::Label());
			this->explbl = (gcnew System::Windows::Forms::Label());
			this->expValue = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// scorelbl
			// 
			this->scorelbl->AutoSize = true;
			this->scorelbl->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->scorelbl->Location = System::Drawing::Point(1052, 25);
			this->scorelbl->Name = L"scorelbl";
			this->scorelbl->Size = System::Drawing::Size(49, 17);
			this->scorelbl->TabIndex = 0;
			this->scorelbl->Text = L"Score:";
			// 
			// hplbl
			// 
			this->hplbl->AutoSize = true;
			this->hplbl->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->hplbl->Location = System::Drawing::Point(1070, 50);
			this->hplbl->Name = L"hplbl";
			this->hplbl->Size = System::Drawing::Size(31, 17);
			this->hplbl->TabIndex = 3;
			this->hplbl->Text = L"HP:";
			this->hplbl->UseMnemonic = false;
			// 
			// scoreValue
			// 
			this->scoreValue->AutoSize = true;
			this->scoreValue->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->scoreValue->Location = System::Drawing::Point(1108, 25);
			this->scoreValue->Name = L"scoreValue";
			this->scoreValue->Size = System::Drawing::Size(16, 18);
			this->scoreValue->TabIndex = 4;
			this->scoreValue->Text = L"0";
			// 
			// hpValue
			// 
			this->hpValue->AutoSize = true;
			this->hpValue->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->hpValue->Location = System::Drawing::Point(1108, 50);
			this->hpValue->Name = L"hpValue";
			this->hpValue->Size = System::Drawing::Size(16, 18);
			this->hpValue->TabIndex = 5;
			this->hpValue->Text = L"0";
			// 
			// feedbackLabel
			// 
			this->feedbackLabel->AutoSize = true;
			this->feedbackLabel->Location = System::Drawing::Point(1052, 115);
			this->feedbackLabel->MaximumSize = System::Drawing::Size(200, 200);
			this->feedbackLabel->MinimumSize = System::Drawing::Size(200, 200);
			this->feedbackLabel->Name = L"feedbackLabel";
			this->feedbackLabel->Size = System::Drawing::Size(200, 200);
			this->feedbackLabel->TabIndex = 6;
			this->feedbackLabel->Text = L"Feedback";
			this->feedbackLabel->Click += gcnew System::EventHandler(this, &MyForm::label1_Click);
			// 
			// explbl
			// 
			this->explbl->AutoSize = true;
			this->explbl->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->explbl->Location = System::Drawing::Point(1061, 74);
			this->explbl->Name = L"explbl";
			this->explbl->Size = System::Drawing::Size(39, 17);
			this->explbl->TabIndex = 7;
			this->explbl->Text = L"EXP:";
			// 
			// expValue
			// 
			this->expValue->AutoSize = true;
			this->expValue->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->expValue->Location = System::Drawing::Point(1108, 74);
			this->expValue->Name = L"expValue";
			this->expValue->Size = System::Drawing::Size(16, 17);
			this->expValue->TabIndex = 8;
			this->expValue->Text = L"0";
			this->expValue->Click += gcnew System::EventHandler(this, &MyForm::label1_Click_1);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1264, 681);
			this->Controls->Add(this->expValue);
			this->Controls->Add(this->explbl);
			this->Controls->Add(this->feedbackLabel);
			this->Controls->Add(this->hpValue);
			this->Controls->Add(this->scoreValue);
			this->Controls->Add(this->hplbl);
			this->Controls->Add(this->scorelbl);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->Shown += gcnew System::EventHandler(this, &MyForm::MyForm_Shown);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		//variable declarations
		GameManager^ theManager;
		Graphics^ mainCanvas;
		Graphics^ offScreenCanvas;
		Bitmap^ img;
		Bitmap^ offScreenBitmap;
		Random^ rGen;
	

	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) 
	{
				 //set up the screen
				 mainCanvas = CreateGraphics();
				 offScreenBitmap = gcnew Bitmap(CANVASWIDTH, CANVASHEIGHT);
				 offScreenCanvas = Graphics::FromImage(offScreenBitmap);
				 rGen = gcnew Random();

				 //create game manager
				 theManager = gcnew GameManager(offScreenCanvas, rGen, feedbackLabel, timer1);//create game manager 
				 theManager->makeDungeon();//make a new dungeon
				 theManager->makePlayer();//initialize the player
				 theManager->setUpGame();//fill the dungeon with items and monsters
				 timer1->Start();//start the timer
				 
				 
	}
	private: System::Void MyForm_Shown(System::Object^  sender, System::EventArgs^  e) 
	{
				 
	}
	
	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) 
	{
				 	 theManager->runGame();//run the game
					 mainCanvas->DrawImage(offScreenBitmap, 0, 0);
					 hpValue->Text = theManager->getPlayerHP().ToString();//update the HP label on the right hand side of the form
					 scoreValue->Text = theManager->score.ToString();//update the score label on the right hand side of the form
					 expValue->Text = theManager->exp.ToString();//update the EXP label on the right hand side of the form
					 feedbackLabel->Text = theManager->feedback;//update the feedback label on the right hand side of the form
					
					 //stop the timer if the player's HP is less than or equal to zero
				 if (theManager->gameOver == true)
					 timer1->Stop();

	}
			 //key  event handler
	private: System::Void MyForm_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) 
	{
				 switch (e->KeyData)
				 {
				 case Keys::Left:
					 theManager->setPlayerDirection(EDirection::WEST);
					 theManager->movePlayer();
					 break;
				 case Keys::Up:
					 theManager->setPlayerDirection(EDirection::NORTH);
					 theManager->movePlayer();
					 break;
				 case Keys::Right:
					 theManager->setPlayerDirection(EDirection::EAST);
					 theManager->movePlayer();
					 break;
				 case Keys::Down:
					 theManager->setPlayerDirection(EDirection::SOUTH);
					 theManager->movePlayer();
					 break;

				 }
	}
	private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
	}
private: System::Void label1_Click_1(System::Object^  sender, System::EventArgs^  e) {
}
};
}
