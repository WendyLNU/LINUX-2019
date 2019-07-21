package com.hzh.judgeBeta1;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.ObjectOutputStream;
import java.io.Serializable;

import javax.jms.BytesMessage;
import javax.jms.Connection;
import javax.jms.ConnectionFactory;
import javax.jms.Destination;
import javax.jms.JMSException;
import javax.jms.MessageProducer;
import javax.jms.Session;
import javax.jms.TextMessage;

import org.apache.activemq.ActiveMQConnectionFactory;
import org.apache.activemq.command.ActiveMQObjectMessage;

import com.domain.Judge;

public class producer {
	 //服务地址，端口默认61616
    private static final String url="tcp://127.0.0.1:61616";
    //这次发送的消息名称
    private static final String topicName="queue_style";
    public static void main(String[] args) throws JMSException, IOException {
        //0. 先判断端口是否启动了  Active MQ 服务器
      //  ActiveMQUtil.checkServer();
        //1.创建ConnectiongFactory,绑定地址
        ConnectionFactory factory=new ActiveMQConnectionFactory(url);
        //2.创建Connection
        Connection connection= factory.createConnection();
        //3.启动连接
        connection.start();
        //4.创建会话
        Session session=connection.createSession(false, Session.AUTO_ACKNOWLEDGE);
        //5.创建一个目标 (队列类型)
        Destination destination=session.createQueue(topicName);
        //6.创建一个生产者
        MessageProducer producer=session.createProducer(destination);
 
      //  for (int i = 0; i < 100; i++) {
            //7.创建消息
  
		
        Judge obj = new Judge();
		
		obj.setJudge_id(123456);
		obj.setCode("[<>]dnfh#gjhgfhdfhjgjvkjsafj");
		
		ActiveMQObjectMessage msg = (ActiveMQObjectMessage) session
	            .createObjectMessage();
		
            //8.发送消息
		
	    msg.setObject((Serializable) obj);
	    //将对象发送
	    producer.send(msg);
      //  }
        //7. 关闭连接
	    System.out.println("success");
        connection.close();
    }
}
