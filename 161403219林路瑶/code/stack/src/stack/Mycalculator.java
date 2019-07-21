package stack;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Stack;

class MyException extends Exception{
    public MyException() {
        super();
    }
    public MyException(String message) {
        super(message);
    }
}

public class Mycalculator extends JFrame{
    /*
     * 
     */

    private JTextField textField;               //�����ı���
    private String input;                       //���
    private String operator;                    //������

    public Mycalculator() {
        input = "";
        operator = "";

        JPanel panel = new JPanel();
        textField = new JTextField(30);
        textField.setEditable(false);                       //�ı����ֹ�༭
        textField.setHorizontalAlignment(JTextField.LEFT);
        //textField.setBounds(100, 100, 20, 20);            //����������Ϊ���������Ч
        textField.setPreferredSize(new Dimension(200,30));//���ø�����ĳ�ʼ��С

        //��textField���뱾JFrame�У�����Ϊ�߽粼�֣�λ��Ϊnorth
        this.add(textField, BorderLayout.NORTH);

        String[] name= {"7","8","9","+","4","5","6","-","1","2","3","*","0","C","=","/"};

        //�����panel�Ĳ�������Ϊ���񲼾֣����������У��м����м��Ϊ1
        panel.setLayout(new GridLayout(4,4,1,1));

        for(int i=0;i<name.length;i++) {

            JButton button = new JButton(name[i]);

            //���ð�ť��ʱ�����
            button.addActionListener(new MyActionListener());
            //����ť���뵽panel��
            panel.add(button);
        }
        //��panel���뵽��JFrame�У�����Ϊ�߽粼�֣�λ��Ϊcentre
        this.add(panel,BorderLayout.CENTER);
    }

    class MyActionListener implements ActionListener{           //�ڲ���ʵ�ְ�ť��Ӧ

        @Override
        public void actionPerformed(ActionEvent e) {
            int cnt=0;
            String actionCommand = e.getActionCommand();            //��ȡ��ť�ϵ��ַ���
            if(actionCommand.equals("+") || actionCommand.equals("-") || actionCommand.equals("*")
                || actionCommand.equals("/")) {
                input += " " + actionCommand + " ";
            }
            else if(actionCommand.equals("C")) {                    //�������
                input = "";
            }
            else if(actionCommand.equals("=")) {                    //���µȺ�
                try {
                    input+= "="+calculate(input);
                } catch (MyException e1) {
                    if(e1.getMessage().equals("����������Ϊ0"))
                        input = e1.getMessage();
                    else
                        input = e1.getMessage();
                }
                textField.setText(input);
                input="";
                cnt = 1;
            }
            else
                input += actionCommand;                         //��������

            //��Ϊ���������=����ťcntһֱδ0�����Կ��Ա�֤��ʾ��������ֺͲ�����
            if(cnt == 0)
                textField.setText(input);
        }
    }
    //������Ҫ����ջ����ɱ��ʽ�ļ��㣬���Ƚ��ַ����ָ���ַ������飬
    //����׺�Ķ���֪��������λΪ��������ӵ�0λ��ʼ����ż��λΪ��������
    // ��˿ɽ�ż��Ϊ��������ջ������+(-)�����������һ��������(��������ʽѹ��ջ�У�
    // ����*��/���������ջ��Ԫ�س�ջ�������һԪ�ؽ��м��㣬������������ѹ��ջ�У�
    // ֱ���������������һ��Ԫ�ء�

    private String calculate(String input) throws MyException{              //���㺯��
        String[] comput = input.split(" ");
        //System.out.println(input);
        Stack<Double> stack = new Stack<>();
        Double m = Double.parseDouble(comput[0]);
        stack.push(m);                                      //��һ����������ջ

        for(int i = 1; i < comput.length; i++) {
            if(i%2==1) {
                if(comput[i].equals("+"))
                    stack.push(Double.parseDouble(comput[i+1]));
                if(comput[i].equals("-"))
                    stack.push(-Double.parseDouble(comput[i+1]));
                if(comput[i].equals("*")) {                 //��ǰһ������ջ���˷�����ջ
                    Double d = stack.peek();                //ȡջ��Ԫ��
                    stack.pop();
                    stack.push(d*Double.parseDouble(comput[i+1]));
                }
                if(comput[i].equals("/")) {                 //��ǰһ������ջ���˷�����ջ
                    double help = Double.parseDouble(comput[i+1]);
                    if(help == 0)
                        throw new MyException("����������Ϊ0");           //�������ִ�иú���
                    double d = stack.peek();
                    stack.pop();
                    stack.push(d/help);
                }
            }
        }

        double d = 0d;

        while(!stack.isEmpty()) {           //���
            d += stack.peek();
            stack.pop();
        }

        String result = String.valueOf(d);
        return result;
    }

    public static void main(String[] args) {
        JFrame f = new Mycalculator();
        f.setTitle(f.getClass().getSimpleName());
        f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        f.setBounds(400, 200, 500, 300);
        f.setVisible(true);
    }
}
