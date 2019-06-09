from  PyQt5.Qt import *
import requests, base64, json, re
import os, time
from urllib.parse import unquote, quote


class TimeTool(object):
	@staticmethod
	def getTrainFormatDate(train_date):
		# Tue Jan 22 2019 00:00:00 GMT+0800 (中国标准时间)
		date_arr = time.strptime(train_date, "%Y%m%d")
		time_tamp = time.mktime(date_arr)
		time_local = time.localtime(time_tamp)
		format = "%a %b %d %Y %H:%M:%S GMT+0800 (China Standard Time)"
		return time.strftime(format, time_local)

class Config(object):

	seat_type_map_dic = {
						'1': "hard_seat",
						'9': "business_seat",
						'6': "vip_soft_bed",
						'4': "soft_bed",
						'3': "hard_bed",
						'0': "second_seat",
						'M': "first_seat",
						'F': "move_bed",
						'WZ': "no_seat",

					}

	@staticmethod
	def get_station_file_path():
		current_path = os.path.realpath(__file__)

		current_dir = os.path.split(current_path)[0]

		return current_dir + r'\stations.json'

	@staticmethod
	def get_yzm_file_path():
		current_path = os.path.realpath(__file__)

		current_dir = os.path.split(current_path)[0]

		return current_dir + r'\yzm.jpg'

	@staticmethod
	def get_email_file_path():
		current_path = os.path.realpath(__file__)

		current_dir = os.path.split(current_path)[0]

		return current_dir + r'\email_account.txt'


class API(object):

	# 设置请求头
	headers = {
		'User-Agent': 'Mozilla / 5.0(WindowsNT10.0;Win64;x64) AppleWebKit / 537.36(KHTML, likeGecko) Chrome / 73.0.3683.103Safari / 537.36',
		'X-Requested-With': 'XMLHttpRequest',
		'Refer': 'XMLHttpRequest'
	}

	#下载验证码  get

	pic_url = 'https://kyfw.12306.cn/passport/captcha/captcha-image64'

	#校验验证码  get

	CHECK_YZM_URL = 'https://kyfw.12306.cn/passport/captcha/captcha-check'

	# refer  get
	Referer_URL = 'https://kyfw.12306.cn/otn/resources/login.html'

	# uamtk-static post
	Uamtk_static_URL = 'https://kyfw.12306.cn/passport/web/auth/uamtk-static'

	# 获取登录所需的cookies——RAIL_DEVICEID和RAIL_EXPIRATION  get



	Logdevice_URL = 'https://kyfw.12306.cn/otn/HttpZF/logdevice'

	# 获取cookies——route post

	Route_URL = 'https://kyfw.12306.cn/otn/login/conf'

	#账号密码验证  post


	CHECK_ACCOUNT_PWD_URL = 'https://kyfw.12306.cn/passport/web/login'

	# uamtk POST
	# appid: otn
	UAMTK_URL = "https://kyfw.12306.cn/passport/web/auth/uamtk"

	# authorclient POST
	# tk: KrNT5--fk1jnBrqFZYHMqoaEH_Ps9hvYfjd8yOBKnemEVFKs275250
	AUTHOR_URL = "https://kyfw.12306.cn/otn/uamauthclient"

	# 问好 POST
	HELLOW_URL = "https://kyfw.12306.cn/otn/index/initMy12306Api"

	# 验证用户是否登录  POST  _json_att:
	IS_LOGIN_URL = 'https://kyfw.12306.cn/otn/login/checkUser'

	# 获取所有的城市 get

	STATIONS_URL = 'https://kyfw.12306.cn/otn/resources/js/framework/station_name.js?station_version=1.9099'

	# 查询车次信息 get
	# leftTicketDTO.train_date: 2019 - 04 - 11
	# leftTicketDTO.from_station: CDW
	# leftTicketDTO.to_station: FZS
	# purpose_codes: ADULT

	QUERY_TICKETS_URL = 'https://kyfw.12306.cn/otn/leftTicket/query'

	# 提交订单信息 POST

	SUBMIT_ORDER_REQUEST_URL = 'https://kyfw.12306.cn/otn/leftTicket/submitOrderRequest'

	# initDC  POST  _json_att:

	INIT_DC_URL = 'https://kyfw.12306.cn/otn/confirmPassenger/initDc'


	# 获取身份证信息  POST
	# _json_att:
	# REPEAT_SUBMIT_TOKEN: 0
	# effdc2f54be0efdd22593aed92d89e1 (通过上面initDC获取)

	PassengerDTO_URL = 'https://kyfw.12306.cn/otn/confirmPassenger/getPassengerDTOs'

	# 检查订单信息  post
	CheckOrder_URL = 'https://kyfw.12306.cn/otn/confirmPassenger/checkOrderInfo'

	# 获取队列个数 post
	QueueCount_URL = 'https://kyfw.12306.cn/otn/confirmPassenger/getQueueCount'


	# 确认订单

	ConfirmSingleForQueue_URL = "https://kyfw.12306.cn/otn/confirmPassenger/confirmSingleForQueue"

class APITool(QObject):

	session = requests.session()  #保持会话

	@classmethod
	def download_yzm(cls):

		# 获取base64加密过后的验证码

		params = {
			'login_site': 'E',
			'module': 'login',
			'rand': 'sjrand',
			int(round(time.time() * 1000)): '',
			'callback': 'jQuery191041991890783655794_1550883477363',
			'_': int(round(time.time() * 1000))
		}

		# ——获取Response——
		response = cls.session.get(API.pic_url, params=params, headers=API.headers)

		html = response.text

		# ——用正则表达式将加密后的验证码提取成json文件——

		jsondata = re.findall('\/\*\*\/.*?\((.*?)\).*?', html)[0]

		dic = json.loads(jsondata)


		# ——使用base64解码——

		img = base64.b64decode(dic['image'])

		yzm_file_path = Config.get_yzm_file_path()

		with open(yzm_file_path, 'wb') as f:
			f.write(img)

		return yzm_file_path

	@classmethod
	def check_yzm(cls, yzm):

		params = {
			'callback': 'jQuery19106171398666659758_1555409634668',
			'answer': yzm,
			'rand': 'sjrand',
			'login_site': 'E',
			'_': int(round(time.time() * 1000))
		}
		# print(params)
		response = cls.session.get(API.CHECK_YZM_URL, params=params, headers=API.headers)
		# print(response.text)
		result = re.findall(r'"result_code":"(.*?)"', response.text)[0]
		# print(cls.session.cookies)
		# print(type(result))
		return result == '4'

	@classmethod
	def get_cookies(cls):
		params = {
			'algID': 'pKLII3uPX6',
			'hashCode': '3iazfzx59XDbYkGwCyrGYM6 - EPV_6MZE0MBQTX_8lmE',
			'FMQw': '0',
			'q4f3': 'zh - CN',
			'VySQ': 'FGGvevcAPOe1PZbSLC11CJ2JfW34duJW',
			'VPIf': '1',
			'custID': '133',
			'VEek': 'unknown',
			'dzuS': '0',
			'yD16': '0',
			'EOQP': '8f58b1186770646318a429cb33977d8c',
			'lEnu': '3232235887',
			'jp76': '52d67b2a5aa5e031084733d5006cc664',
			'hAqN': 'Win32',
			'platform': 'WEB',
			'ks0Q': 'd22ca0b81584fbea62237b14bd04c866',
			'TeRS': '1040x1920',
			'tOHY': '24xx1080x1920',
			'Fvje': 'i1l1o1s1',
			'q5aJ': '-8',
			'wNLf': '99115dfb07133750ba677d055874de870',
			'aew': 'Mozilla / 5.0(WindowsNT10.0;Win64;x64) AppleWebKit / 537.36(KHTML, likeGecko) Chrome / 73.0.3683.103Safari / 537.36',
			'E3gR': '819842ed8dc137a3ecfcea9f9b45d061',
			'timestamp': int(round(time.time() * 1000))
		}
		rep = cls.session.get(API.Logdevice_URL, params=params, headers=API.headers)
		# # print(rep.text)
		# RAIL_DEVICEID = re.findall(r'"dfp":"(.*?)"', rep.text)[0]
		# RAIL_EXPIRATION = re.findall(r'"exp":"(.*?)"', rep.text)[0]
		# return (RAIL_DEVICEID, RAIL_EXPIRATION)


		cls.session.post(API.Route_URL, headers=API.headers)

		cls.session.get(API.Referer_URL, headers=API.headers)

		cls.session.post(API.Uamtk_static_URL, headers=API.headers)



		#最近浏览器标识生成算法一直变导致的无法动态获取上面两个cookie，只能先复制网站的cookie硬编码

		cls.session.cookies.set('RAIL_EXPIRATION', '1560007318997')
		cls.session.cookies.set('RAIL_DEVICEID', 'CShHAQOicEZWtQOPIQJ2hTvvVn2D_IMbT5cMvUxuOCmO-YNocji84noxYoKqFAo0q3FE48KOlMPAIqGmF70KYi0c5feObf5tTJCVMcBCbXgOg3mjeekPmRFuERUDYZPY1UXctew2eFAfJZRfamgZSQ1TT4odYTdm')




	@classmethod
	def check_account_pwd(cls, account, pwd, result):
		# print(account)
		# print(pwd)
		# print(result)
		print('开始验证账号密码')
		cls.get_cookies()

		headers = {
			'User-Agent': 'Mozilla / 5.0(WindowsNT10.0;Win64;x64) AppleWebKit / 537.36(KHTML, likeGecko) Chrome / 73.0.3683.103Safari / 537.36',
			'Referer': 'https://kyfw.12306.cn/otn/resources/login.html',
			'Content-Type': 'application/x-www-form-urlencoded; charset=utf-8',
			'X-Requested-With': 'xmlHttpRequest',
			'Connection': 'keep-alive',
			'Host': r'kyfw.12306.cn',
			'is_logger': 'True',
			'is_json': 'True'
		}

		data_dic = {
			'username': account,
			'password': pwd,
			'appid': 'otn',
			'answer': result
		}


		response = cls.session.post(API.CHECK_ACCOUNT_PWD_URL, data=data_dic, headers=headers, allow_redirects=False)
		print('传输完毕')
		print(cls.session.cookies)
		dic = response.json()
		print(dic)
		result_code = response.json()['result_code']
		if result_code == 0:
			cls.author()
			return " ".join(cls.get_hello())
		else:
			return None


	@classmethod
	def author(cls):
		resoponse = cls.session.post(API.UAMTK_URL, data={"appid": "otn"})
		tk = resoponse.json()["newapptk"]
		res2 = cls.session.post(API.AUTHOR_URL, data={"tk": tk})

	@classmethod
	def get_hello(cls):
		response = cls.session.post(API.HELLOW_URL)
		dic = response.json()
		if dic['httpstatus'] == 200:
			return (dic['data']['user_name'], dic['data']['user_regard'])
		return ("", "")

	@staticmethod
	def get_all_stations_reverse():# 将站名和电报码反转，用以匹配
		dic = APITool.get_all_stations()
		reverse_dic = {value: key for key, value in dic.items()}
		return reverse_dic


	@staticmethod
	def get_all_stations():
		# 1.检查本地是否有对应的缓存
		# 2.有 直接加载并返回出去
		if os.path.exists(Config.get_station_file_path()):
			print('读取缓存')
			with open(Config.get_station_file_path(), 'r', encoding='utf-8') as f:
				result = json.loads(f.read(), encoding='utf-8')

				return result
		else:
			print('网络请求下载的站点数据')
		# 3.没有  发送网络请求，请求结果保存到本地进行缓存

			station_dic = {}
			resp = requests.get(API.STATIONS_URL)
			items = resp.text.split('@')
			for item in items:
				station_list = item.split('|')
				if len(station_list) != 6:
					continue
				city_name = station_list[1]
				city_code = station_list[2]
				station_dic[city_name] = city_code
			print(station_dic)
			with open(Config.get_station_file_path(), 'w', encoding='utf-8') as f:
				json.dump(station_dic, f)
			return station_dic


	@classmethod
	def query_tickets(cls, train_date, from_station, to_station, purpose_codes, seat_type=None):


		cls.query_dic = {
			'train_date': train_date,
			'purpose_codes': purpose_codes,
			'seat_type': seat_type
		}



		code2station = APITool.get_all_stations_reverse()
		query_params = {
			'leftTicketDTO.train_date': train_date,
			'leftTicketDTO.from_station': from_station,
			'leftTicketDTO.to_station': to_station,
			'purpose_codes': purpose_codes
		}
		resp = requests.get(API.QUERY_TICKETS_URL, params=query_params)

		result = resp.json()
		trainDicts = []
		if result['httpstatus'] == 200:

			items = result['data']['result']

			for item in items:
				trainDict = {}

				trainInfo = item.split('|')
				if trainInfo[11] == 'Y':  # 是否可以预定
					trainDict['secret_str'] = trainInfo[0]  # 车次密文字符串(下订单时使用)
					trainDict['train_num'] = trainInfo[2]  # 车次编号 24000000Z30L
					trainDict['train_name'] = trainInfo[3]  # 车次名称，如D352
					trainDict['from_station_code'] = trainInfo[6]  # 出发地电报码
					trainDict['to_station_code'] = trainInfo[7]  # 目的地地电报码
					trainDict['from_station_name'] = code2station[trainInfo[6]]  # 出发地名称 手动实现 北京
					trainDict['to_station_name'] = code2station[trainInfo[7]]  # 目的地名称 手动实现 上海
					trainDict['start_time'] = trainInfo[8]  # 出发时间
					trainDict['arrive_time'] = trainInfo[9]  # 到达时间
					trainDict['total_time'] = trainInfo[10]  # 总用时
					trainDict['left_ticket'] = trainInfo[
						12]  # 余票 wrlmtI6BmBd8izygoiCBbpr3%2B%2BGKdIk1SHpJdJ1f6w1p%2FhGF
					trainDict['train_date'] = trainInfo[13]  # 火车日期 20190121
					trainDict['train_location'] = trainInfo[15]  # P4 后期用
					trainDict["vip_soft_bed"] = trainInfo[21]  # 高级软卧
					trainDict['other_seat'] = trainInfo[22]  # 其他
					trainDict["soft_bed"] = trainInfo[23]  # 软卧
					trainDict["no_seat"] = trainInfo[26]  # 无座
					trainDict["hard_bed"] = trainInfo[28]  # 硬卧
					trainDict["hard_seat"] = trainInfo[29]  # 硬座
					trainDict["second_seat"] = trainInfo[30]  # 二等座
					trainDict["first_seat"] = trainInfo[31]  # 一等座
					trainDict["business_seat"] = trainInfo[32]  # 商务座
					trainDict["move_bed"] = trainInfo[33]  # 动卧


					if seat_type == None:
						trainDicts.append(trainDict)
					else:
						key = Config.seat_type_map_dic[seat_type]
						if trainDict[key] == '有' or trainDict[key].isdigit():
							trainDicts.append(trainDict)


				print(trainDict)

		else:
			print('数据请求错误')
		return trainDicts


	@classmethod
	def check_login(cls):
		rep = cls.session.post(API.IS_LOGIN_URL, data={'_json_att': ''})
		is_login = rep.json()['data']['flag']
		return is_login

	@classmethod
	def submit_order_request(cls, trainDict):  # 提交订单请求

		data_dic = {
			'secretStr': unquote(trainDict['secret_str']),
			'train_date': cls.query_dic['train_date'],
			'back_train_date': cls.query_dic['train_date'],
			'tour_flag': 'dc',
			'purpose_codes': cls.query_dic['purpose_codes'],
			'query_from_station_name': trainDict['from_station_name'],
			'query_to_station_name': trainDict['to_station_name'],
			'undefined': ''
		}

		rep = cls.session.post(API.SUBMIT_ORDER_REQUEST_URL, data=data_dic)
		status = rep.json()['status']
		if not status:
			print(rep.json()['messages'])
			return False
		print('继续订票')
		return True


	@classmethod
	def initDc(cls):  # 获取乘客信息所需要传递的参数
		rep = cls.session.post(API.INIT_DC_URL, data={'_json_att':''})
		try:
			token = re.findall(r"var globalRepeatSubmitToken = '(.*?)'", rep.text)[0]
			key_check_isChange = re.findall(r"'key_check_isChange':'(.*?)'", rep.text)[0]

			return (token, key_check_isChange)
		except:
			return None

	@classmethod
	def get_PassengerDTO(cls, token):
		# token = cls.initDc()
		data_dic = {
			'_json_att': '',
			'REPEAT_SUBMIT_TOKEN': token
		}
		rep = cls.session.post(API.PassengerDTO_URL, data=data_dic)
		result = rep.json()
		print(result)
		if not result['status']:
			print('获取乘客信息失败')
			return None
		name = cls.get_hello()[0]
		for dic in result['data']['normal_passengers']:
			if dic['passenger_name'] == name:
				return dic

		return None

	@classmethod
	def checkOrder(cls, seatType, passengerDic, token):


		data_dic = {
			"cancel_flag": "2", # 固定
			"bed_level_order_num": "000000000000000000000000000000", # 固定
			"passengerTicketStr": "{},{},{},{},{},{},{},N".format(seatType, passengerDic["passenger_flag"], #座位席别
																  passengerDic["passenger_type"],#用户类型 学生3 普通1
																  passengerDic["passenger_name"],#名字
																  passengerDic["passenger_id_type_code"],#身份证类型
																  passengerDic["passenger_id_no"],#身份证号
																  passengerDic["mobile_no"]),#手机号

			"oldPassengerStr": "{},{},{},3_".format(passengerDic["passenger_name"],
													passengerDic["passenger_id_type_code"],
													passengerDic["passenger_id_no"]),

			"tour_flag": "dc",
			"randCode": "",
			"whatsSelect": "1",
			"_json_att": "",
			"REPEAT_SUBMIT_TOKEN": token

		}
		print('——'*30,'CheckOrder','——'*30, data_dic)
		rep = cls.session.post(API.CheckOrder_URL, data=data_dic)
		result = rep.json()
		if result['status'] and result['data']['submitStatus']:
			print('检查订单成功')
			return True
		return False

	@classmethod
	def getQueueCount(cls, trainDic, seatType, token):
		data_dic = {

			"train_date": TimeTool.getTrainFormatDate(trainDic["train_date"]),
			"train_no": trainDic["train_num"],
			"stationTrainCode": trainDic["train_name"],
			"seatType": seatType,
			"fromStationTelecode": trainDic["from_station_code"],
			"toStationTelecode": trainDic["to_station_code"],
			"leftTicket": trainDic["left_ticket"],
			"purpose_codes": "00", # 固定
			"train_location": trainDic["train_location"],
			"_json_att": "",
			"REPEAT_SUBMIT_TOKEN": token

		}
		print('——' * 30, 'getQueueCount', '——' * 30, data_dic)
		rep = cls.session.post(API.QueueCount_URL, data=data_dic)
		result = rep.json()
		if not result['status']:
			print('查询队列消息失败')
			return False
		print('查询队列个数成功', result['data']['ticket'])
		return True

	@classmethod
	def confirm_queue(cls, seatType, token, key_check_isChange, passengerDic, trainDic):

		data_dic = {
			"passengerTicketStr": "{},{},{},{},{},{},{},N".format(seatType, passengerDic["passenger_flag"],
																  passengerDic["passenger_type"],
																  passengerDic["passenger_name"],
																  passengerDic["passenger_id_type_code"],
																  passengerDic["passenger_id_no"],
																  passengerDic["mobile_no"]),
			"oldPassengerStr": "{},{},{},3_".format(passengerDic["passenger_name"],
													passengerDic["passenger_id_type_code"],
													passengerDic["passenger_id_no"]),
			"randCode": "", # 固定
			"purpose_codes": "00",# 固定
			"key_check_isChange": key_check_isChange,  # 在initDC里，跟获取token同时得
			"leftTicketStr": trainDic["left_ticket"],
			"train_location": trainDic["train_location"],
			"choose_seats": "",  # 位置随机
			"seatDetailType": "000", #固定
			"whatsSelect": "1",#固定
			"roomType": "00",#固定
			"dwAll": "N",#固定
			"_json_att": "",#固定
			"REPEAT_SUBMIT_TOKEN": token
		}
		print('——' * 30, 'confirmqueue', '——' * 30, data_dic)
		rep = cls.session.post(API.ConfirmSingleForQueue_URL, data=data_dic)

		result = rep.json()

		return result['status'] and result['data']['submitStatus'] # 都是ture则返回Ture

	@classmethod
	def buy_ticket(cls, trainDict = None):  # 确认用户是否登录
		if not cls.check_login():
			print('请先登录账户')
			return False

		print(trainDict)

		if not cls.submit_order_request(trainDict):		# 提交订单请求
			print('提交订单失败')
			return False
		token, key_check_isChange  = cls.initDc()
		passenger = cls.get_PassengerDTO(token)
		print(passenger)
		if not cls.checkOrder(cls.query_dic['seat_type'], passenger, token): # 检查订单
			print('检查订单失败')
			return False
		if not cls.getQueueCount(trainDict, cls.query_dic['seat_type'], token):  # 查询队列个数，查询成功再次确认订单
			print('查询队列个数失败')
		if not cls.confirm_queue(cls.query_dic['seat_type'], token, key_check_isChange, passenger, trainDict):
			print('预定失败')
		return True






if __name__ == '__main__':
	APITool.download_yzm()