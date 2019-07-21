package com.util;

import java.io.Serializable;

import javax.jms.Connection;
import javax.jms.ConnectionFactory;
import javax.jms.Destination;
import javax.jms.JMSException;
import javax.jms.MessageProducer;
import javax.jms.Session;

import org.apache.activemq.ActiveMQConnectionFactory;
import org.apache.activemq.command.ActiveMQObjectMessage;

import com.domain.Judge;

import cn.hutool.core.util.NetUtil;



public class ActiveMqUtil {
	 //服务地址，端口默认61616
    private static final String url="tcp://127.0.0.1:61616";
    //这次发送的消息名称
    private static final String topicName="queue_style";
    private static ConnectionFactory factory=null;

    private Connection connection = null;
    private Session session = null;
    
    public MessageProducer getProducer()
    {
    	if(NetUtil.isUsableLocalPort(8161)) {
            System.out.println("ActiveMQ 服务器未启动 ");
            return null;
        }
    	if(factory == null)
    	factory = new ActiveMQConnectionFactory(url);
		try {
			//2.创建Connection
			connection= factory.createConnection();
	        //3.启动连接
			
	        connection.start();
	        //4.创建会话
	        
			session = connection.createSession(false, Session.AUTO_ACKNOWLEDGE);
	        //5.创建一个目标 (队列类型)
	        Destination destination=session.createQueue(topicName);
	        //6.创建一个生产者
	        return session.createProducer(destination);
		} catch (JMSException e) {
			// TODO Auto-generated catch block
			
			e.printStackTrace();
			
			return null;
		}


    }
    
    public void closeProduer()
    {
    	
			try {
				if(connection!=null)
				connection.close();
			} catch (JMSException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
    }
    
    public void sendJudge(Judge judge)
    {
    	MessageProducer producer = getProducer();
		if(producer!=null)
		{
			try {
				ActiveMQObjectMessage msg = (ActiveMQObjectMessage) session
				        .createObjectMessage();
				msg.setObject((Serializable) judge);
				producer.send(msg);
			} catch (JMSException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		closeProduer();
    }

}
