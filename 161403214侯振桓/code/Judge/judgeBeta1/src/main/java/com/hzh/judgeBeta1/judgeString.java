package com.hzh.judgeBeta1;


import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.channels.FileChannel;

import com.domain.Judge;
import com.hzh.judgeBeta1.JudgeDao;
import com.hzh.judgeBeta1.JudgeDaoImpl;
/*
 * 判题端
 */
public class judgeString extends Thread{
	static {
		//load jni .so
		
		System.loadLibrary("testjni");
	}
	public native String getSolution(String PATH);
	private static String paths = "/home/ubuntu/judge/data";
	private static String pathd = "/home/ubuntu/judge/judge_work";
	private Judge judgeTask;
	
	judgeString(Judge judgeTask)
	{
		this.judgeTask = judgeTask;
	}
	public static void copyFile(File source,File dest) throws IOException
	{
		FileChannel inputChannel = null;
		FileChannel outputChannel = null;
		try {
			inputChannel = new FileInputStream(source).getChannel();
			outputChannel = new FileOutputStream(dest).getChannel();
			outputChannel.transferFrom(inputChannel, 0, inputChannel.size());
		}
		finally {
			inputChannel.close();
			outputChannel.close();
		}
		
	}
	
	public boolean createWork(String PATHS,String PATHD) throws IOException
	{
		File dir = new File(PATHS);
		File dest = new File(PATHD);
		if(dir == null || !dir.exists() || dest.exists()) {
			System.out.println("error:");
			System.out.println(PATHS);
			System.out.println(PATHS);
			return false;
		}
		
		if(!dir.isFile()&&dest.mkdir())
		{
			for(File file : dir.listFiles())
			{
			
				if(file.getName().endsWith(".in"))
				{
					
					File destFilePath = new File(PATHD + "/" + file.getName());
					int len = file.getName().length();
					File outFile = new File(PATHS + "/" + file.getName().substring(0, len-2)+"out");
					File destoutFilePath = new File(PATHD + "/" + outFile.getName());
					if(!outFile.exists())
					{
						FileWriter fw = new FileWriter(PATHD+ "/" + "error.log");
						fw.write("not found "+outFile.getName());
						fw.close();
						return false;
					}
					
						
					copyFile(file,destFilePath);
					copyFile(outFile,destoutFilePath);
			
					//System.out.println(file.getName());
				}
				
			}
			
			
			FileWriter fw = new FileWriter(PATHD+ "/" + "Main.cc");
			fw.write(judgeTask.getCode());
			fw.close();

		}
		
		return true;
	}

	
	@Override
	public void run() {
		try {
			int ACflag=0;
			if( createWork(paths+"/"+judgeTask.getProblem_id(),pathd+"/"+judgeTask.getJudge_id()) )
			{
				System.out.println("yes");
				String aaaString = String.format("%s#%d#%d#",pathd+"/"+judgeTask.getJudge_id(),judgeTask.getTime(),judgeTask.getSpace()/1000 + 1);
				System.out.println(aaaString);
				String result = getSolution(aaaString);
				int f = 1,num = 0;
				for(char c:result.toCharArray())
				{
					if(c=='#')
					{
						if(f==1)
						{
							judgeTask.setStatus(num);
							System.out.println("Status:"+num);
						}
						if(f==2)
						{
							judgeTask.setTime(num);
							System.out.println("Time:"+num+"ms");
						}
						if(f==3)
						{
							judgeTask.setSpace(num/1000);
							System.out.println("Space:"+num/1000+"kB");
						}
						num=0;
						f++;
					}
					else num = num * 10+c-'0';
				}
				JudgeDao dao = new JudgeDaoImpl();
				dao.update(judgeTask);
			}
			else {
				ACflag=1;
				System.out.println("no");
			}
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		finally {
			Judge2.run_threads--;
		}
		
		
	}

}
