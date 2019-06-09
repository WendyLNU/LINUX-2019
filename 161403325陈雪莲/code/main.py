from PyQt5.Qt import *
from Login_Pane import LoginPane
from Query_Pane import QueryPane


if __name__ == '__main__':
	import sys

	app = QApplication(sys.argv)

	print('登录界面显示')
	login_pane = LoginPane()
	login_pane.setWindowTitle("fuck12306") # 设置标题窗口

	login_pane.show()
	# login_pane.hide()

	query_pane = QueryPane()


	def success_login_slot(content):
		login_pane.hide()
		query_pane.setWindowTitle(content)
		query_pane.show()


	login_pane.success_login.connect(success_login_slot)
	login_pane.show()
	sys.exit(app.exec_())