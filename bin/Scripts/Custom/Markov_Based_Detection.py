from GUI import GUI,Widget,EventType
from GUIUtility import GUIUtility
import qt_module_wrapped
from plt import plt
from Debug import Debug
import csv

class Markov_Based_Detection(Widget):
	def __init__(self):
		super().__init__()

	def OnGUI(self):
		GUI.BeginGUI(self)

		GUI.BeginGroup("Detection Setting")
		GUI.BeginHorizontalLayout()
		GUI.Label("IPDs文件")
		GUI.LineEdit("edit_ipds_file")
		GUI.Button("button_openipds","打开文件")
		GUI.EndLayout()
		GUI.EndGroup()

		GUI.BeginHorizontalLayout()
		GUI.Spacer(400)
		GUI.Button("button_drawIPDs","绘制IPDs图像")
		GUI.EndLayout()

		GUI.EndGUI()

	@GUI.Slot(receiver = "button_openipds",eventType=EventType.Button_Click)
	def OnClick_OpenIPDsFile(self):
		GUI.set.SetLineEditText(self,"edit_ipds_file",GUIUtility.AskOpenFile("打开隐蔽信道IPDs文件","CSV File(*.csv)"))

	@GUI.Slot(receiver = "button_drawIPDs",eventType=EventType.Button_Click)
	def OnClick_DrawIPDsFile(self):
		path = GUI.get.GetLineEditText(self,"edit_ipds_file")
		if not path:
			Debug.printWarning("无法绘制图像：IPDs文件为空")
			return
		def readCSV(filePath,start= 0 ,end=-1)->list:
			ans = []
			with open(filePath) as f:
				reader = csv.reader(f)
				next(reader)
				next(reader)
				for row in reader:
					try:
						ans.append((float)(row[0]))
					except ValueError as ve:
						Debug.printError(str(ve))
			return ans
		ipds = readCSV(path)[0:150000]
		Debug.printInfo("读取完成，开始排序...")
		ipds.sort()
		Debug.printInfo("排序完成")
		plt.figure(1)
		plt.plot(x= list(range(len(ipds))),y = ipds,seriesName = "IPCTC",rgb = [0,0,255],lineWidth = 5,xlabel = "Times",ylabel = "Inter-packet delay",windowTitle = "TRCTC信道排序后 IPDs 分布规律")
		plt.displayAll()
		
	def OnStart(self):
		GUI.set.SetControlEnabled(self,"edit_ipds_file",False)

	def OnClose(self):
		pass