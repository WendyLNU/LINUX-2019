package com.hzh.judgeBeta1;

import javax.jms.JMSException;

import com.domain.Judge;

/**
 * Hello world!
 *
 */
public class App 
{
    public static void main( String[] args )
    {	String debugString = null;
    	if(args != null && args.length>0) {
    		System.out.println(args[0]);
    		debugString = args[0];
    	}
        System.out.println( "Hello Judge!" );
        try {
			Judge2.mainRun(debugString);
		} catch (JMSException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
    }
}
