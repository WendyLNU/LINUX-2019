from PyQt5.Qt import *

class DIYLabel(QLabel):

	def auto_add_point(self, result):



			# self.create_point_btn(QPoint(center_x - 10, center_y - 10))
		point_rep = result.split('|')
		for item in point_rep:
			rsp = {}
			rsp[0] = item.split(',')[0]
			rsp[1] = item.split(',')[1]


			self.create_point_btn(QPoint(int(rsp[0]), int(rsp[1])))

	def clear_point(self):
		[child.deleteLater() for child in self.children() if child.inherits('QPushButton')]

	#——将鼠标点击的坐标结果保存——
	def get_result(self):

		result = ','.join(['{},{}'.format(child.x() + 10, child.y() - 20) for child in self.children() if child.inherits('QPushButton')])

		print(result)
		# for child in self.children():
		# 	if child.inherits('QPushButton'):
		# 		print(child.pos())
		return result

	def mousePressEvent(self, evt):
		super().mousePressEvent(evt)
		#——打印鼠标点击坐标——
		print(evt.pos())
		#判断是否点到上方无效区域
		if evt.x() < 0 or evt.y() <= 30:
			return None
		self.create_point_btn(evt.pos() - QPoint(10, 10))


	def create_point_btn(self, pt):
		#——设置点击出现红点——
		point = QPushButton(self)
		point.resize(20, 20)
		point.move(pt)
		point.setStyleSheet('background-color: red; border-radius: 10px;')
		point.show()

		#——设置双击消除红点


		point.clicked.connect(lambda _, btn=point: btn.deleteLater())