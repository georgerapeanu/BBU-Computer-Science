package controller.parsers.expressions;

/* Expression grammar:
    expr = (expr)
    expr = term/factor/... operator expr
    expr = name
    expr = constant/true/false
 */

import controller.parsers.expressions.exceptions.InvalidExpressionAppException;
import controller.parsers.expressions.exceptions.WrongMatchAppException;
import model.expressions.BinaryExpression;
import model.expressions.ConstantExpression;
import model.expressions.IExpression;
import model.expressions.VariableExpression;
import model.values.BooleanValue;
import model.values.IntegerValue;
import utils.RefInt;

import java.sql.Ref;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import static java.lang.Math.exp;
import static java.lang.Math.max;

public class ExpressionParser {

    private static int extractInteger(String string, RefInt position) throws WrongMatchAppException {
        int pos = position.getValue();
        if(!(Character.isDigit(string.charAt(pos)) || string.charAt(pos) == '-')){
            throw new WrongMatchAppException("No integer here");
        }
        int sign = 1;
        if(string.charAt(pos) == '-'){
            sign = -1;
            pos += 1;
        }
        if(pos >= string.length() || !Character.isDigit(string.charAt(pos))){
            throw new WrongMatchAppException("No integer here");
        }

        int answer = 0;

        while(pos < string.length() && Character.isDigit(string.charAt(pos))){
            answer = answer * 10 + string.charAt(pos) - '0';
            pos += 1;
        }

        position.setValue(pos);
        return answer * sign;
    }

    private static boolean extractBoolean(String string, RefInt position) throws WrongMatchAppException {
        if(position.getValue() + 3 < string.length()){
            if(string.substring(position.getValue(), position.getValue() + 4).equals("true")) {
                position.increase(4);
                return true;
            }
        }
        if(position.getValue() + 4 < string.length()){
            if(string.substring(position.getValue(), position.getValue() + 5).equals("false")) {
                position.increase(5);
                return false;
            }
        }
        throw new WrongMatchAppException("No boolean here");
    }

    private static String extractName(String string, RefInt position) throws InvalidExpressionAppException {
        StringBuilder name = new StringBuilder();
        List<Character> delimiterTokens = new ArrayList<>();
        for(String[] operator_list: OperatorPriority.operators){
            for(String operator: operator_list){
                if(operator.length() > 1){
                    continue;
                }
                delimiterTokens.add(operator.charAt(0));
            }
        }
        delimiterTokens.add('(');
        delimiterTokens.add(')');
        delimiterTokens.add(' ');

        while(!delimiterTokens.contains(string.charAt(position.getValue()))) {
            name.append(string.charAt(position.getValue()));
            position.increase(1);
        }
        if(name.length() == 0){
            throw new InvalidExpressionAppException("Invalid name");
        }
        return name.toString();
    }

    private static IExpression extractTerm(String string, RefInt position) throws InvalidExpressionAppException {
        if(string.charAt(position.getValue()) == '('){
            position.increase(1);
            IExpression tmp = parseAtPositionWithOperator(string, position, 0);
            if(position.getValue() >= string.length() ||  string.charAt(position.getValue()) != ')') {
                throw new InvalidExpressionAppException("Expression is invalid, unbalanced paranthesis");
            }
            position.increase(1);
            return tmp;
        }
        try{
            return new ConstantExpression(new BooleanValue(extractBoolean(string, position)));
        } catch (WrongMatchAppException e) {
            ;
        }
        try{
            return new ConstantExpression(new IntegerValue(extractInteger(string, position)));
        } catch (WrongMatchAppException e) {
            ;
        }
        return new VariableExpression(extractName(string, position));
    }

    private static String extractOperator(String string, RefInt position, String[] currentOperators) {
        while(position.getValue() < string.length() && string.charAt(position.getValue()) == ' '){
            position.increase(1);
        }
        if(position.getValue() >= string.length()){
            return null;
        }
        List<String> operators = new ArrayList<>();
        int minLength = -1;
        int maxLength = -1;
        for(String operator: currentOperators){
            operators.add(operator);
            maxLength = max(maxLength, operator.length());
            if(minLength == -1 || minLength > operator.length()){
                minLength = operator.length();
            }
        }

        for(int length = minLength;length <= maxLength;length++){
            if(position.getValue() + length - 1 >= string.length()){
                break;
            }
            if(operators.contains(string.substring(position.getValue(), position.getValue() + length))){
                position.increase(length);
                return string.substring(position.getValue() - length, position.getValue());
            }
        }

        return null;
    }

    private static IExpression parseAtPositionWithOperator(String string, RefInt position, int currentOperator) throws InvalidExpressionAppException {
        while(position.getValue() < string.length() && string.charAt(position.getValue()) == ' '){
            position.increase(1);
        }
        if(position.getValue() >= string.length()){
            return null;
        }
        if(currentOperator >= OperatorPriority.operators.length) { ///we can assume we have either a variable/constant/true/false either paranthesis
            return extractTerm(string, position);
        }

        IExpression currentExpression = parseAtPositionWithOperator(string, position, currentOperator + 1);
        if(currentExpression == null){
            throw new InvalidExpressionAppException("Something wrong happened");
        }

        while(true){
            if(position.getValue() >= string.length()){
                break;
            }
            String operator = extractOperator(string, position, OperatorPriority.operators[currentOperator]);
            if(operator == null){
                break;
            }
            currentExpression = new BinaryExpression(currentExpression, parseAtPositionWithOperator(string, position, currentOperator), operator);
        }
        return currentExpression;
    }

    public static IExpression parseAtPosition(String string, RefInt position) throws InvalidExpressionAppException {
        IExpression expression = parseAtPositionWithOperator(string, position, 0);
        return expression;
    }

    public static  IExpression parse(String string) throws InvalidExpressionAppException {
        IExpression expression = parseAtPositionWithOperator(string, new RefInt(0), 0);
        return expression;
    }
}
