//
//  main.cpp
//  infixStack
//
//  Created by Preferred Customer on 10/23/19.
//  Copyright © 2019 humza choudry. All rights reserved.
//

#include <iostream>
#include <stack>
#include <string>

using namespace std;


class stackInfixCalculator{
private:
    
    stack<int>  *oprands;
    stack<char> *operators;
    stack<char> *negativeCheck;
    stack<int> *oprandsFlipped;
    stack<char> *operatorsFlipped;
    string expression;
    bool negativeAlert;
    bool openParentheses;
    bool stackFlipped;
    bool isNegative;
    bool multiplyOrDivide;
    bool entireStack;
    bool untilParentheses;
    int openParenthesesCount;
    int numberOfOperators;
    

void printResult(bool flippedStack){
    
    if (flippedStack == false) {
        int result = oprands->top();
        oprands->pop();
        cout << "Solution = " << result << endl;
    }
    else {
        int result = oprandsFlipped->top();
        oprandsFlipped->pop();
        cout << "Solution = " << result << endl;
    }
}
    
void clearFlipStacks(){
            
    while (!oprandsFlipped->empty()) {
            oprandsFlipped->pop();
    }
    while (!operatorsFlipped->empty()) {
            operatorsFlipped->pop();
        
    }
            
}
    
string createExpressionWithoutParentheses(){
            
    string newExpression;
    unsigned long sizeOfStack = oprandsFlipped->size();
        
// create a new expression using the stacks. First append the oprand then the operator.
     for (int i =0; i < sizeOfStack; i++) {
        
        string v = to_string(oprandsFlipped->top());
        oprandsFlipped->pop();
        newExpression += v;
        
        if (i <  sizeOfStack-1) {
            newExpression += operatorsFlipped->top();
            operatorsFlipped->pop();
        }
     }

    return newExpression;
}
    
void additionAndSubtraction(bool parenthesesOrNot){
    
// Computation will be different if the stack is flipped. Therefore, set stackFlipped to 'true'.
// If first parse function is called then bool is 'true' and compute until '(' is reached, which means until numberOfOperators = 0.
// Otherwise, third function is the caller. All that remains is +/- in express. Compute until operator stack is empty.
// Value of numberOfOperators is set by the flipStacks() function.
    
    stackFlipped = true;
    
    if (parenthesesOrNot == true) {
        
        while (numberOfOperators != 0) {
            oprandsFlipped->push(compute(oprandsFlipped, operatorsFlipped));
            numberOfOperators--;
            }
        
            oprands->push(oprandsFlipped->top());
            oprandsFlipped->pop(); // make sure stack is empty, contains final answer for (+/-)
            stackFlipped = false;
    }
    else {
        stackFlipped = true;
        while (!operatorsFlipped->empty()) {
            oprandsFlipped->push(compute(oprandsFlipped, operatorsFlipped));
        }
        stackFlipped = false;
    }

}
    
void flipStacks(){
          
//If bool is true, then flip the stack until '(' is reached. Place all values into new stack. Remove the '(' that is left in the stack.
// if bool is false, secondParse() is the caller. Flip the entire stack (both) and place values into new stack.
    
  numberOfOperators = 0;

  if (untilParentheses == true) {

      if (operatorsFlipped->empty()) {
             
             while (operators->top() != '(') {
                operatorsFlipped->push(operators->top());
                 operators->pop();
                 numberOfOperators++;
             }
          }
                 
                 
      operators->pop(); // remove the '('
      int numberOfOprands = numberOfOperators + 1; // # of oprands in the stack is equal to the # number of operators in the stack plus one.

      if (oprandsFlipped->empty()) {
                 
          while (numberOfOprands != 0) {
                 oprandsFlipped->push(oprands->top());
                 oprands->pop();
                 numberOfOprands--;
             }
        }
      stackFlipped = true;
      untilParentheses = false;
}
  else if (entireStack == true) {

      if (oprandsFlipped->empty()) {
          
          while (!oprands->empty()) {
              oprandsFlipped->push(oprands->top());
              oprands->pop();
          }
      }
      
      if (operatorsFlipped->empty()) {
          
          while (!operators->empty()) {
              operatorsFlipped->push(operators->top());
              operators->pop();
          }
      }
      stackFlipped = true;
      entireStack = false;
  }

}
    
int compute(stack<int> *num, stack<char> *op) {
        
// Computation is different if stack has been flipped or not. If stack has been flipped then Second - First becomes First - Second.
    int first = num->top();
    num->pop();
    int second = num->top();
    num->pop();
    char whatOperation = op->top();
    op->pop();
     
    if (!stackFlipped) {
    if (whatOperation == '+')
        return first+second;
    else if(whatOperation == '-')
        return second-first;
    else if(whatOperation == '*')
         return second *first;
    else if(whatOperation == '-')
         return second-first;
    else if(whatOperation == '/'){
        if (first == 0){
            throw string("Cannot divide by zero! ");
          }
        return second / first;
        }
    }
    else {
        
        if (whatOperation == '+')
               return first+second;
           else if(whatOperation == '-')
               return first - second;
           else if(whatOperation == '*')
                return first * second;
           else if(whatOperation == '-')
                return first - second;
           else if(whatOperation == '/'){
               if (first == 0){
                   throw string("Cannot divide by zero! ");
               }
               return first / second;
           }
        
    }
    throw string("Error in compute function.");
}
    
void negativeOrNot(char expressionValue){
            
// first condition checks to see if an operator '-' is the first symbol in the expression. Ex. -2+3.
// If the operator is deemed not a negative symbol then add to the opertor stack.
// negativeAlert value is set by the operatorOrNot function.
    if (operators->empty() && oprands->empty()) {
        isNegative = true;
    }
    else if(negativeAlert == false){
            operators->push(expressionValue);
    }

}
    
void checkForNegative(char op){
        
// negativeCheck stack pushes everything it comes accross in the expression.
// if top is '(' and op is equal to '-' then it is a negative number. Ex. (-2+3).
// if top is not a digit and op is an operator then it is a negative number. Ex. 2+-3.

   if (isdigit(negativeCheck->top())){
       negativeCheck->push(op);

   }
   else if (negativeCheck->top() == '(' && op == '-'){
       negativeCheck->push(op);
       negativeAlert = true;
   }
   else {
       negativeCheck->push(op);
       negativeAlert = true;
     }

}
    
bool operatorOrNot(char op){
        
    if (op=='+'||op=='-'||op=='/'||op=='*')
    return true;
    else
        return false;
}
    
int getFullOprand(int indexExpression){

// While loop: keep going until oprandChar is not a digit. Once loop exists, return the new place in the string via an index.
// Ex. 22+3. indexExpression = 0, loop until '+' is reached and then return index - 1. This is done for the forloop in the parse/secondParse function. Forloop will continue in the string where this function stopped at minus one.

// if any negative bool is true then multiply by - 1. Push into stack.
// negativeCheck pushes '2' here becuase everything in the expression must be pushed onto this stack to check for negative numbers. negativeOrNot function uses this stack.
    
  char oprandChar = expression[indexExpression];
  int num = 0;
  
  while (isdigit(oprandChar)) {
          num = num*10 + (oprandChar-'0');
          indexExpression++;

      if(indexExpression < expression.length())
        oprandChar = expression[indexExpression];
        else
            break;
    } indexExpression--;
              
   if (negativeAlert || isNegative) {
        int turnNeg = num * - 1;
        oprands->push(turnNeg);
        isNegative = false;
        negativeAlert = false;
        negativeCheck->push('2');
    }
    else {
        negativeCheck->push('2');
        oprands->push(num);
   }

  return indexExpression;
}
    
void divideOrMultiply(bool computeOrNot){
      
// parse functions check if * or / is the last element in stack. If it is then multiplyOrDivide = true. Following this function, the number after * or / will be pushed onto stack. Then this function will be called again to compute * or /.
    if (computeOrNot == false) {
        multiplyOrDivide = false;
 
      if (!operators->empty() && (operators->top() == '*' || operators->top() == '/')) {
          multiplyOrDivide = true;
        }
  }
  else
      oprands->push(compute(oprands, operators));

}

void thirdParse(){
        
    // All that remains at this point is an expression with only + and/or -. Since the stack being used here has been prevously flipped, parameter value is false for flipStack.
    if (oprandsFlipped->empty() && operatorsFlipped->empty()) {
        entireStack = true;
        flipStacks();
        additionAndSubtraction(false);
    }
    
    bool printFlippedStack = true;
    printResult(printFlippedStack);
    
}

void secondParse(){
    
// Ex. at this point the expression has gone from 2+(3*2)-1 to 2+6-1. Expression inside parentheses has been solved.
// Flip original stacks(oprand, operators), append to create new string using flipped stacks values. Then clear the flipped stacks.
// Then go through the update expression and ONLY do * or /. And push solution onto stack.
    entireStack = true;
    flipStacks();
    expression = createExpressionWithoutParentheses();
    clearFlipStacks();

    for(int i=0; i< expression.length();i++) {
        char c = expression[i];
         
        if(isdigit(c)){
            
            divideOrMultiply(false);
            i = getFullOprand(i);
            
            if (multiplyOrDivide == true)
                divideOrMultiply(true);
          }
          else if(operatorOrNot(c))
                negativeOrNot(c);
         else
            continue;

    }

// First condition is true is expression only contain multiplication and/or division, outside of parentheses. Otherwise, Continue onto thirdParse, to handle addition and subtraction.
    if (operators->empty()){
        bool printFlippedStack = false;
        printResult(printFlippedStack);
    }
    else
        thirdParse();

}

public:
    
void parse(string expression){
// Push all oprands and operators onto the stack
// only calculate the solution for the expression inside of the parentheses. Push solution onto stack.
// Go through expression, if it is a digit then get the reminder of the number if multi-digit.
// check if the top() operator in the operator stack is * or / (multiplyOrDivide function)
// if express had a '(' prevously (openParentheses = true) And if
    
    this->expression = expression;

    for(int i=0; i < expression.length();i++) {
        char c = expression[i];
        
        if(isdigit(c)){
            divideOrMultiply(false);
            i = getFullOprand(i);
           
            if (openParentheses == true && openParenthesesCount != 0 && multiplyOrDivide == true)
                divideOrMultiply(true);
        }
        else if(c=='('){
            operators->push(c);
             negativeCheck->push(c);
            openParentheses = true;
            openParenthesesCount++;
        }
        else if(c==')') {
            openParenthesesCount--;
            // if there are multiple open '(' (more then one) then it contains a nested '('. Bool will remain true, that way expression inside () is fully computed. Only compute if one or more '(' exist. Otherwise dont compute and keep pushing elements onto stack.
            if (openParenthesesCount == 0)
                openParentheses =false;
            
            if (operators->top() == '(')
                operators->pop();
            else {
                untilParentheses = true;
                flipStacks();
                additionAndSubtraction(true);

            }
            
        }
        else if(operatorOrNot(c))
            negativeOrNot(c);
        else if (c != ' ') // Something other then an oprand/operator/parentheses/space
            throw string("Invaild Entry. Only numbers and operators allowed.");
        else
            continue; // if space continue
}

// if first condition is true. Expression only contained parentheses. Otherwise expression contains more then just parentheses or no parentheses
    if (operators->empty()){
        bool printFlippedStack = false;
        printResult(printFlippedStack);
    }
    else
        secondParse();
}

stackInfixCalculator(){
            oprands = new stack<int>();
            operators = new stack<char>();
            negativeCheck = new stack<char>();
            oprandsFlipped = new stack<int>();
            operatorsFlipped = new stack<char>();
            openParentheses = false;
            stackFlipped = false;
            isNegative = false;
            openParenthesesCount = 0;
            numberOfOperators = 0;
            multiplyOrDivide = false;
            negativeAlert = false;
            untilParentheses = false;
            entireStack = false;
}
    
~stackInfixCalculator(){
            delete oprands;
            delete operators;
            delete negativeCheck;
            delete oprandsFlipped;
            delete operatorsFlipped;
}
    
};



int main() {
    /*
    Algorithm:
    1) parse(): parse and solve expression inside of parentheses ONLY.
    2) secondParse(): if expression contains more then just parentheses OR contains no parentheses. Here only handle multiplication and division outside of parentheses.
    3) thirdParse(): to handle addition and subtraction in the expression.
    */
    
    cout << "Enter an expression to calculate." << endl << "Rules:" << endl << "Only Multiplication, Division, Subtraction, and Division are allowed" << endl << "Parentheses, Nested Parentheses, Negative Numbers, and Multi-digit Numbers are allowed" << endl;
    
    stackInfixCalculator infixCalculator;
    string userEnteredExpression;
    getline(cin, userEnteredExpression);
    
    try {
     infixCalculator.parse(userEnteredExpression);
    }
    catch(string exceptionString) {
        cout << exceptionString << endl;
    }
    

    return 0;
}
