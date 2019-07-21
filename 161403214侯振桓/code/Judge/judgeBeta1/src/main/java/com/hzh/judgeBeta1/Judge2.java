package com.hzh.judgeBeta1;

import java.util.Collections;
import java.util.LinkedList;
import java.util.List;

import javax.jms.BytesMessage;
import javax.jms.Connection;
import javax.jms.ConnectionFactory;
import javax.jms.Destination;
import javax.jms.JMSException;
import javax.jms.Message;
import javax.jms.MessageConsumer;
import javax.jms.MessageListener;
import javax.jms.ObjectMessage;
import javax.jms.Session;
import javax.jms.TextMessage;
 
import org.apache.activemq.ActiveMQConnectionFactory;

import com.domain.Judge;

import cn.hutool.core.util.NetUtil;
import cn.hutool.core.util.RandomUtil;
/*
 * 题目入口
 */
public class Judge2 {
	
	private static List<Judge> problemQueue = Collections.synchronizedList(new LinkedList<Judge>()) ;

	public static  volatile int run_threads = 0;
    //服务地址，端口默认61616
    private static final String url="tcp://127.0.0.1:61616";
    //这次消费的消息名称
    private static final String topicName="queue_style";
 
    //消费者有可能是多个，为了区分不同的消费者，为其创建随机名称
    private static final String consumerName="consumer-" + RandomUtil.randomString(5);
    
	public static void mainRun( String debugString) throws JMSException
	{
		// ActiveMQUtil.checkServer();
		if(debugString != null && debugString.equals("debug")) {
			Judge p = new Judge();
			p.setJudge_id(1001);
			p.setProblem_id(1001);
			p.setTime(1000);
			p.setSpace(5000);
			p.setCode("#include<iostream> \r\n using namespace std; \r\n int main(){ int a,b; cin>>a>>b; cout<<a+b<<endl; return 0;}");
			judgeString jc = new judgeString(p);
   		 	jc.start();
   		 	try {
				jc.join();
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			System.out.println(p.getCode());
			return;
		}
		if(NetUtil.isUsableLocalPort(8161)) {
            System.out.println("ActiveMQ 服务器未启动 ");
            return;
        }
	        System.out.printf("%s 消费者启动了。 %n", consumerName);
	 
	        //1.创建ConnectiongFactory,绑定地址
	        ActiveMQConnectionFactory factory=new ActiveMQConnectionFactory(url);
	        factory.setTrustAllPackages(true);
	        //2.创建Connection
	        Connection connection= factory.createConnection();
	        //3.启动连接
	        connection.start();
	        //4.创建会话
	        Session session=connection.createSession(false, Session.AUTO_ACKNOWLEDGE);
	        //5.创建一个目标 （主题类型）
	        Destination destination=session.createQueue(topicName);
	        //6.创建一个消费者
	        MessageConsumer consumer=session.createConsumer(destination);
	        //7.创建一个监听器
	        
	        consumer.setMessageListener(new MessageListener() {
	 
	            public void onMessage(Message arg0) {
	                
	            	 if (arg0 != null) {
                         try {
                        	 Judge p = (Judge)((ObjectMessage) arg0).getObject();
							if(problemQueue.size()<1000)	problemQueue.add(p);
							//System.out.println(p.getJudge_id());
							//System.out.println(p.getCode());
							
						} catch (JMSException e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						}
	            	 }
	            	 else System.out.println("null?");
	 
	            }
	        });
		
		/*Problem p1 = new Problem(); 
		p1.setProblem_id(1001);
		p1.setJudge_id(100001);
		p1.setCode("#include<c++>");
		problemQueue.add(p1);*/
	     while(true)
	     {
	    	 if(problemQueue.isEmpty()||run_threads >= 3)
	    	 {
	    		 try {
					Thread.sleep(1000);
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
	    	 }
	    	 else
	    	 {
	    		 run_threads++;
	    		 Judge p = problemQueue.remove(0);
	    		 judgeString jc = new judgeString(p);
	    		 jc.start();
	    	 }
	     }
	       
	}

}

