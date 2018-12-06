
pragma solidity ^0.5.0;

contract BrooklynToken {

// Set the contract owner
    address public owner = msg.sender;

    // Initialize tokenName
    string public tokenName;

    // Initialize tokenSymbol
    string public tokenSymbol;

    // Initialize _totalSupply    
    uint public initialSupply;

    // Create an array with all balances
    mapping (address => uint256) public balanceOf;
    
    // function that will deploy our smart contract
    // constructor (uint256 initialSupply, string _tokenName, string _tokenSymbol) public {
    constructor (){
        // Give the initial supply to the contract owner
        // balanceOf[owner] = initialSupply;

        // // Set the token name
        // tokenName = _tokenName;

        // // Set the token symbol
        // tokenSymbol = _tokenSymbol;

        tokenSymbol = "BKNTKN";
        tokenName = "BrooklynToken";
        initialSupply = 1000;

        // Give the initial supply to the contract owner
        balanceOf[owner] = initialSupply;

    }

    // enable ability to transfer tokens
    function transfer(address _to, uint256 _value) public returns (bool success) {

        // Check if the sender has enough
        require(balanceOf[msg.sender] >= _value);

        // Check for integer overflows
        require(balanceOf[_to] + _value >= balanceOf[_to]);

        // Subtract value from the sender
        balanceOf[msg.sender] -= _value;

        // Add value to recipient
        balanceOf[_to] += _value;

        // Return true if transfer is successful
        return true;

    }

}

