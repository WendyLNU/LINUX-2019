import smtplib
from email.mime.text import MIMEText
from email.utils import formataddr
from API.API_Tool import Config

my_sender = ''  # 发件人邮箱账号
my_pass = ''  # 发件人邮箱密码

class Mail():


	@classmethod
	def mail(cls):
		reciver_path = Config.get_email_file_path()
		with open(reciver_path, 'r') as f:
			reciver = f.read()
			print(reciver)
		if len(reciver) != 0:

			ret = True

			my_user = reciver  # 收件人邮箱账号，我这边发送给自己
			print(my_user)

			try:
				msg = MIMEText('您好，购票成功，请尽快去支付订单', 'plain', 'utf-8')
				msg['From'] = formataddr(["Howe1l", my_sender])  # 括号里的对应发件人邮箱昵称、发件人邮箱账号
				# print('1')
				msg['To'] = formataddr(["用户", my_user])  # 括号里的对应收件人邮箱昵称、收件人邮箱账号
				# print('2')
				msg['Subject'] = "12306购票成功，请尽快去完成订单"  # 邮件的主题，也可以说是标题
				# print('3')
				server = smtplib.SMTP_SSL("smtp.163.com", 465)  # 发件人邮箱中的SMTP服务器，端口是465
				server.login(my_sender, my_pass)  # 括号中对应的是发件人邮箱账号、邮箱密码
				# print('4')
				server.sendmail(my_sender, [my_user, ], msg.as_string())  # 括号中对应的是发件人邮箱账号、收件人邮箱账号、发送邮件
				# print('5')
				server.quit()  # 关闭连接
			except Exception:  # 如果 try 中的语句没有执行，则会执行下面的 ret=False
				ret = False
				print('失败')
			return ret




	# ret = Mail.mail()
	# if ret:
	# 	print("邮件发送成功")
	# else:
	# 	print("邮件发送失败")

if __name__ == '__main__':
	a = Mail()
	a.mail()

