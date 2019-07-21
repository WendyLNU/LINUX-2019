from PyQt5.Qt import *
from resource.login_ui import Ui_Form
from API.API_Tool import APITool, Config
from lianzhong_api import main



class DownLoadYZMThread(QThread):
    get_yzm_url_signal = pyqtSignal(str)
    def run(self):
        url = APITool.download_yzm()
        # print("下载验证码")
        self.get_yzm_url_signal.emit(url)

class DMThread(QThread):
	get_yzm_result_signal = pyqtSignal(str)

	def __init__(self, url, parent=None):
		super().__init__(parent)
		self.yzm_url = url


	def run(self):

		url = self.yzm_url.replace('\\','/')
		result = main(url)
		self.get_yzm_result_signal.emit(result)


class LoginPane(QWidget, Ui_Form):
	success_login = pyqtSignal(str)

	def __init__(self, parent=None, *args, **kwargs):
		super().__init__(parent, *args, **kwargs)
		self.setupUi(self)
		self.refresh_yzm()

	def refresh_yzm(self):

		print('刷新验证码')
		thread = DownLoadYZMThread(self)

		def parse_yzm_url(url):
			self.current_url = url
			pixmap = QPixmap(url)
			self.yzm_label.setPixmap(pixmap)
			self.yzm_label.clear_point()

		thread.get_yzm_url_signal.connect(parse_yzm_url)
		thread.start()
		print("继续主线程任务")

	def auto_dm(self):
		print("自动打码")
		# print(self.current.url)
		self.auto_dm_btn.setEnabled(False)
		thread = DMThread(self.current_url, self)

		def parse_yzm_result(result):
			print(result)
			self.auto_dm_btn.setEnabled(True)
			if result != "0":
				self.yzm_label.auto_add_point(result)
			else:
				print("自动打码失败")

		thread.get_yzm_result_signal.connect(parse_yzm_result)
		thread.start()


	def check_login(self):
		print('登录')

		#——调用get_result方法将鼠标点击的坐标结果保存——
		result = self.yzm_label.get_result()

		if len(result) == 0:   #如果验证码没有点击，则不发送请求
			print('请点击验证码')
			return None


		if APITool.check_yzm(result):

			print('验证码正确')

			account = self.account_le.text()
			pwd = self.pwd_le.text()
			reciver = self.email_le.text()
			reciver_path = Config.get_email_file_path()
			with open(reciver_path, 'w+') as f:
				f.write(reciver)

			result_str = APITool.check_account_pwd(account, pwd, result)
			if result_str is None:
				QMessageBox.warning(self, '错误提示', '账号或密码错误，登录失败') #弹窗警告，标题，内容
				self.yzm_label.clear_point()
				self.refresh_yzm()
				return None
			self.success_login.emit(result_str)

		else:
			print('验证码错误')
			self.yzm_label.clear_point()
			self.refresh_yzm()

	def auto_enable_login_btn(self):

		#——设置账号密码没有输入登录按钮不能点击——

		# print('自动设置登录按钮的有效性')
		account = self.account_le.text()
		pwd = self.pwd_le.text()
		if len(account) == 0 or len(pwd) == 0:
			self.login_btn.setEnabled(False)
		else:
			self.login_btn.setEnabled(True)



if __name__ == '__main__':

	import sys

	app = QApplication(sys.argv)


	login = LoginPane()

	login.show()

	sys.exit(app.exec_())