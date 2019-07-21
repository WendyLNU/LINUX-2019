from PyQt5.Qt import *
from resource.query_pane import Ui_Form
from API.API_Tool import APITool
from Book_Pane import BookPane
from email_tool import Mail

class QueryPane(QWidget, Ui_Form):
	def __init__(self, parent=None, *args, **kwargs):
		super().__init__(parent, *args, **kwargs)
		self.tj = {'zw': None, 'phone_num': None}
		self.setupUi(self)
		self.setupBookPane()
		self.setupData()

	def resizeEvent(self, evt):# 设置抢票下拉选项框大小自适应
		super().resizeEvent(evt)
		self.book_pane.resize(self.width(), self.query_pane_top.height())


	def hide_book_pane(self):

		# 关闭动画效果
		animation = QPropertyAnimation(self.book_pane, b'pos', self.book_pane)
		animation.setEndValue(QPoint(0, -self.book_pane.height()))
		animation.setStartValue(QPoint(0, 0))
		animation.setDuration(1000)
		animation.setEasingCurve(QEasingCurve.OutBounce)
		animation.start(QAbstractAnimation.DeleteWhenStopped)

	def show_book_pane(self):
		# 设置动画效果
		animation = QPropertyAnimation(self.book_pane, b'pos', self.book_pane)
		animation.setStartValue(QPoint(0, -self.book_pane.height()))
		animation.setEndValue(QPoint(0, 0))
		animation.setDuration(1000)
		animation.setEasingCurve(QEasingCurve.OutBounce)
		animation.start(QAbstractAnimation.DeleteWhenStopped)

	def setupBookPane(self):
		# 设置点击抢票出现下拉选项
		self.book_pane = BookPane(self)

		# 设置接受信号
		self.book_pane.confirm_signal.connect(self.book_ticket_filter)
		self.book_pane.cancel_signal.connect(self.cancel_query)
		self.book_pane.resize(self.width(), 130)
		self.book_pane.move(0, -self.book_pane.height())
		# self.book_pane.show()


	def setupData(self):

		# 设置下拉文本框匹配出发地/目的地信息

		dic = APITool.get_all_stations()
		self.from_station_cb.addItems(dic.keys())
		self.to_station_cb.addItems(dic.keys())

		#******出发地******

        # 键入匹配，下拉显示
		completer = QCompleter(dic.keys())
		self.from_station_cb.setCompleter(completer)

		def check_data(cb):# 当未选择或输入完整城市名便点击其他地方，回到默认选项
			current_city = cb.currentText()
			result = dic.keys().__contains__(current_city)
			if not result:
				cb.setCurrentIndex(0)
			pass

		self.from_station_cb.lineEdit().editingFinished.connect(lambda: check_data(self.from_station_cb))

		#*****目的地*****
		completer2 = QCompleter(dic.keys())
		self.to_station_cb.setCompleter(completer2) # 键入匹配

		self.to_station_cb.lineEdit().editingFinished.connect(lambda: check_data(self.to_station_cb))

		# 日期设置当前时间且以前的日期不可选
		self.start_date_de.setDate(QDate.currentDate())
		self.start_date_de.setMinimumDate(QDate.currentDate())

		###未设置什么时间段可以选学生票


		#设置表格的头部数据
		model = QStandardItemModel(self.tickets_tv)

		# 设置模型的头部数据
		headers = ['车次', '出发站->到达站', '出发时间-到达时间', '历时', '商务座-特等座', '一等座', '二等座',
				   '高级-软卧', '软卧-一等卧', '动卧', '硬卧-二等卧', '硬座', '无座', '其他']


		model.setColumnCount(len(headers))
		for idx, title in enumerate(headers):# 枚举
			model.setHeaderData(idx, Qt.Horizontal, title)

		self.tickets_tv.setModel(model)


	def filter_tickets(self):  #查询票
		print('查询')
		dic = APITool.get_all_stations()

		# 获取出发日期
		start_date = self.start_date_de.text()

		# 获取出发地
		from_city_code = dic[self.from_station_cb.currentText()]

		# 获取目的地
		to_city_code = dic[self.to_station_cb.currentText()]

		# 获取票的类型  普通/学生
		purpose_codes = self.buttonGroup.checkedButton().property('q_value')

		result = APITool.query_tickets(start_date, from_city_code, to_city_code, purpose_codes, seat_type=self.tj['zw'])
		# print(result)

		return result



	def query_tickets(self):# 将查询票的结果展示

		result = self.filter_tickets()
		model = self.tickets_tv.model()
		# QStandardItemModel().setRowCount()
		model.setRowCount(len(result))
		columns = ['train_name', ('from_station_name', 'to_station_name'), ('start_time', 'arrive_time'),
		 'total_time', 'business_seat', 'first_seat', 'second_seat', 'vip_soft_bed', 'soft_bed', 'move_bed',
		 'hard_bed', 'hard_seat', 'no_seat', 'other_seat']

		for row, train_dic in enumerate(result):
			print(train_dic)
			for column, column_name in enumerate(columns):
				if type(column_name) == str:
					model.setItem(row, column, QStandardItem(train_dic[column_name]))
				else:
					tmp = '->'.join([train_dic[key] for key in column_name])
					model.setItem(row, column, QStandardItem(tmp))


		self.tickets_tv.setModel(model)

		return result


	def book_ticket_filter(self, tj): # 取出座次条件
		# self.hide_book_pane()
		# print(tj)
		self.tj = tj
		self.timer.start(7000)  #点击确定开始定时器，7S一次




	def book_tickets(self):
		print('抢票')

		self.show_book_pane()
		self.timer = QTimer(self)
		self.timer.timeout.connect(self.buy_ticket)


	def buy_ticket(self):
		result = self.query_tickets()
		if len(result):
			self.cancel_query()
			print('当前有车票，正在购买')
			success = APITool.buy_ticket(result[0])
			if success:
				print('订票成功，请立即去支付')
				Mail.mail()
				QMessageBox.information(self, '订票成功！', '订票成功，请立即去支付')  # 弹窗，标题，内容

			else:
				print('订票失败')
				QMessageBox.warning(self, '错误提示', '订票失败')  # 弹窗警告，标题，内容


		else:
			print('当前没有车票')


	def cancel_query(self):
		print('停止定时器')
		self.timer.stop()
		self.hide_book_pane()




if __name__ == '__main__':
	import sys

	app = QApplication(sys.argv)



	query_pane = QueryPane()

	# 设置窗口标题

	# query_pane.setWindowTitle()

	query_pane.show()



	sys.exit(app.exec_())
