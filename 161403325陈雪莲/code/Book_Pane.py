from PyQt5.Qt import *
from resource.book_pane import Ui_Form



class BookPane(QWidget, Ui_Form):
	# 定义一个信号用于传递
	confirm_signal = pyqtSignal(dict)
	cancel_signal = pyqtSignal()


	def __init__(self, parent=None, *args, **kwargs):
		super().__init__(parent, *args, **kwargs)
		self.setupUi(self)
		self.setAttribute(Qt.WA_StyledBackground, True)
		# self.student_ticket()


	def confirm(self):

		zw = self.buttonGroup.checkedButton().property('val')
		phone_num = self.phone_num_le.text()

		print(zw, phone_num)


		self.confirm_signal.emit({'zw': zw, 'phone_num': phone_num})


	def cancel_query(self):
		self.cancel_signal.emit()


	# def student_ticket(self):
	# 	rep = self.start_date_de.text()
	# 	if int(rep[5:7])>=6 and int(rep[5:7])<=9:
	# 		pass
	# 	elif int(rep[5:7])==12 and int(rep[5:7])<=3:
	# 		pass
	# 	else:
	# 		self.stu_cb.setEnabled(False)



if __name__ == '__main__':
	import sys

	app = QApplication(sys.argv)



	window = BookPane()

	# 设置窗口标题

	# query_pane.setWindowTitle()

	window.show()

	sys.exit(app.exec_())