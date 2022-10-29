package controller.parsers.syntax;

import controller.parsers.expressions.ExpressionParser;
import controller.parsers.expressions.exceptions.InvalidExpressionAppException;
import controller.parsers.syntax.exceptions.SyntaxAppException;
import model.expressions.IExpression;
import model.statements.*;
import model.values.types.BooleanType;
import model.values.types.IType;
import model.values.types.IntegerType;
import utils.RefInt;

import java.util.Arrays;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/*
    TYPE = IntegerType|BooleanType
    NAME="([a-zA-Z_])+[a-zA-Z0-9_]*"
    VariableDeclarationStatement = "TYPE NAME"
    AssignmentStatement = "NAME=Expression"
    IfStatement = "If Expression Then Statement1 else Statement2"
    PrintStatement = "print(Expression)"
    NoOperationStatement = ""
    CompositeStatement = "Statement1;Statement2"
    Statement = {Statement}
 */

public class SyntaxParser {
    private static IType[] types = {new IntegerType(), new BooleanType()};
    private static Character[] whiteSpace = {' ', '\t', '\n', '\r'};
    private static Pattern namePattern = Pattern.compile("^(([a-zA-Z_])+[a-zA-Z0-9_]*)");

    private static void skipWhiteSpace(String string, RefInt position) {
        while(position.getValue() < string.length() && Arrays.asList(whiteSpace).contains(string.charAt(position.getValue()))){
            position.increase(1);
        }
    }
    private static IType extractType(String string, RefInt position) throws SyntaxAppException {
        for(IType type : types){
            if(position.getValue() + type.toString().length() <= string.length() && string.substring(position.getValue(), position.getValue() + type.toString().length()).equals(type.toString())) {
                position.increase(type.toString().length());
                return type;
            }
        }
        throw new SyntaxAppException("No type present");
    }

    private static String extractName(String string, RefInt position) throws SyntaxAppException {
        Matcher matcher = namePattern.matcher(string.substring(position.getValue()));
        if(!matcher.find()){
            throw new SyntaxAppException("No name found");
        }
        String answer = matcher.group(1);
        position.increase(matcher.group(0).length());
        return answer;
    }


    private static IStatement parseAssignment(String string, RefInt position) throws SyntaxAppException, InvalidExpressionAppException {
        skipWhiteSpace(string, position);
        String name = extractName(string, position);
        skipWhiteSpace(string, position);
        if(position.getValue() >= string.length() || string.charAt(position.getValue()) != '=') {
            throw new SyntaxAppException("Invalid assignment");
        }
        position.increase(1);
        skipWhiteSpace(string, position);
        int pos = position.getValue();
        while(pos < string.length() && string.charAt(pos) != ';') {
            pos++;
        }
        IStatement answer = new AssignmentStatement(name, ExpressionParser.parse(string.substring(position.getValue(), pos)));
        position.setValue(pos);
        skipWhiteSpace(string, position);
        if(position.getValue() >= string.length() || string.charAt(position.getValue()) != ';'){
            throw new SyntaxAppException("Invalid syntax, missing ;");
        }
        position.increase(1);
        return answer;
    }

    private static IStatement parseVariableDeclaration(String string, RefInt position) throws SyntaxAppException {
        skipWhiteSpace(string, position);
        IType type = extractType(string, position);
        skipWhiteSpace(string, position);
        String name = extractName(string, position);
        skipWhiteSpace(string, position);
        if(position.getValue() >= string.length() || string.charAt(position.getValue()) != ';'){
            throw new SyntaxAppException("Invalid syntax, missing ;");
        }
        position.increase(1);
        return new VariableDeclarationStatement(name, type);
    }


    private static IStatement parsePrint(String string, RefInt position) throws SyntaxAppException, InvalidExpressionAppException {
        skipWhiteSpace(string, position);
        if(position.getValue() + 5 >= string.length() || !string.substring(position.getValue(), position.getValue() + 6).equals("print(")){
            throw new SyntaxAppException("Invalid print statement");
        }
        position.increase(5);
        int pos = position.getValue();
        while(pos < string.length() && string.charAt(pos) != ';') {
            pos++;
        }
        IStatement answer = new PrintStatement(ExpressionParser.parse(string.substring(position.getValue(), pos)));
        position.setValue(pos);
        skipWhiteSpace(string, position);
        if(position.getValue() >= string.length() || string.charAt(position.getValue()) != ';'){
            throw new SyntaxAppException("Invalid syntax, missing ;");
        }
        position.increase(1);
        return answer;
    }

    private static IStatement parseIf(String string, RefInt position) throws SyntaxAppException, InvalidExpressionAppException {
        skipWhiteSpace(string, position);
        if(position.getValue() + 2 >= string.length()){
            throw new SyntaxAppException("Invalid if syntax");
        }
        String ifBegin = string.substring(position.getValue(), position.getValue() + 3);
        if(!(ifBegin.startsWith("if ") || ifBegin.startsWith("if("))){
            throw new SyntaxAppException("Invalid if syntax");
        }

        position.increase(2);
        IExpression cond = ExpressionParser.parseAtPosition(string, position);
        skipWhiteSpace(string, position);

        String thenBegin = string.substring(position.getValue(), position.getValue() + 5);
        if(!(thenBegin.startsWith("then ") || thenBegin.startsWith("then{"))){
            throw new SyntaxAppException("Invalid if syntax");
        }

        position.increase(4);
        IStatement first = parseNonComposite(string, position);
        skipWhiteSpace(string, position);

        String elseBegin = string.substring(position.getValue(), position.getValue() + 5);
        if(!(elseBegin.startsWith("else ") || elseBegin.startsWith("else{"))){
            throw new SyntaxAppException("Invalid if syntax");
        }

        position.increase(4);
        IStatement second = parseNonComposite(string, position);
        skipWhiteSpace(string, position);

        return new IfStatement(cond, first, second);
    }


    private static IStatement parseNonComposite(String string, RefInt position) throws SyntaxAppException, InvalidExpressionAppException {
        skipWhiteSpace(string, position);
        if(position.getValue() >= string.length()){
            return null;
        }
        if(string.charAt(position.getValue()) == '{') {
            position.increase(1);
            IStatement statement = parseAtPosition(string, position);
            if(string.charAt(position.getValue()) != '}'){
                throw new SyntaxAppException("Invalid syntax");
            }
            position.increase(1);
            return statement;
        }
        if (string.charAt(position.getValue()) == '}'){
            return null;
        }
        if(string.charAt(position.getValue()) == ';'){
            return parseNoOperation(string, position);
        }
        if(position.getValue() + 4 < string.length() && string.substring(position.getValue(), position.getValue() + 5).equals("print")){
            return parsePrint(string, position);
        }
        if(position.getValue() + 2 < string.length() && string.substring(position.getValue(), position.getValue() + 2).equals("if")){
            return parseIf(string, position);
        }
        int pos = position.getValue();
        boolean hasEqual = false;
        while(! hasEqual && pos < string.length() && string.charAt(pos) != ';'){
            hasEqual = (string.charAt(pos) == '=');
            pos++;
        }
        if(hasEqual){
            return parseAssignment(string, position);
        }
        return parseVariableDeclaration(string, position);
    }

    private static IStatement parseNoOperation(String string, RefInt position) throws SyntaxAppException {
        skipWhiteSpace(string, position);
        if(position.getValue() >= string.length()){
            throw new SyntaxAppException("Invalid NOP statement");
        }
        position.increase(1);
        return new NoOperationStatement();
    }

    private static IStatement parseAtPosition(String string, RefInt position) throws SyntaxAppException, InvalidExpressionAppException {
        skipWhiteSpace(string, position);
        if(position.getValue() >= string.length()){
            return null;
        }
        if (position.getValue() < string.length() && string.charAt(position.getValue()) == '}'){
            return null;
        }

        IStatement currentStatement = parseNonComposite(string, position);

        skipWhiteSpace(string, position);
        IStatement nextStatement = parseAtPosition(string, position);
        if(nextStatement == null){
            return currentStatement;
        }
        currentStatement = new CompositeStatement(currentStatement, nextStatement);

        return currentStatement;
    }

    public static IStatement parse(String string) throws SyntaxAppException, InvalidExpressionAppException {
        return parseAtPosition(string, new RefInt(0));
    }
}
