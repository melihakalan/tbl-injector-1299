object Form1: TForm1
  Left = 0
  Top = 0
  BorderStyle = bsSingle
  Caption = 'kojd - tbl injector - 1453'
  ClientHeight = 201
  ClientWidth = 318
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 8
    Width = 61
    Height = 13
    Caption = 'Inject listesi:'
  end
  object Label2: TLabel
    Left = 176
    Top = 141
    Width = 122
    Height = 13
    Caption = 'kojd, www.onlinehile.com'
  end
  object ListBox1: TListBox
    Left = 8
    Top = 27
    Width = 153
    Height = 166
    ItemHeight = 13
    Items.Strings = (
      'Skill_Magic_Main_us.tbl'
      'item_org_us.tbl'
      'skill_magic_4.tbl')
    TabOrder = 0
  end
  object Button1: TButton
    Left = 167
    Top = 66
    Width = 143
    Height = 33
    Caption = 'Toplu inject'
    TabOrder = 1
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 167
    Top = 27
    Width = 143
    Height = 33
    Caption = 'Se'#231'iliyi inject'
    TabOrder = 2
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 167
    Top = 160
    Width = 143
    Height = 33
    Caption = 'Kapat'
    TabOrder = 3
    OnClick = Button3Click
  end
end
