// parts of this script courtesy of Nick's steemit tutorial @hardlydifficult
// https://steemit.com/tutorial/@hardlydifficult/ethereum-dapp-tutorial-part-2-of-3-web-front-end-with-metamask-integration

import Web3 from "web3";

const contract_address="0xd74A0F3606dbc4AD636760a751ecACBBc294D288"; 
const abi = [{"constant":true,"inputs":[],"name":"initialSupply","outputs":[{"name":"","type":"uint256"}],"payable":false,"stateMutability":"view","type":"function"},{"constant":true,"inputs":[],"name":"tokenName","outputs":[{"name":"","type":"string"}],"payable":false,"stateMutability":"view","type":"function"},{"constant":true,"inputs":[{"name":"","type":"address"}],"name":"balanceOf","outputs":[{"name":"","type":"uint256"}],"payable":false,"stateMutability":"view","type":"function"},{"constant":true,"inputs":[],"name":"tokenSymbol","outputs":[{"name":"","type":"string"}],"payable":false,"stateMutability":"view","type":"function"},{"constant":true,"inputs":[],"name":"owner","outputs":[{"name":"","type":"address"}],"payable":false,"stateMutability":"view","type":"function"},{"constant":false,"inputs":[{"name":"_to","type":"address"},{"name":"_value","type":"uint256"}],"name":"transfer","outputs":[{"name":"success","type":"bool"}],"payable":false,"stateMutability":"nonpayable","type":"function"},{"inputs":[{"name":"_initialSupply","type":"uint256"},{"name":"_tokenName","type":"string"},{"name":"_tokenSymbol","type":"string"}],"payable":false,"stateMutability":"nonpayable","type":"constructor"}];


let contract;
let my_web3;
let account;
const rpcUrl = "https://ropsten.infura.io";

window.addEventListener('load', () => {
    let msg = document.getElementById("message");
    msg.style.display = "none";
    if(typeof(web3) === 'undefined') {
    //   return console.log("Metamask is not installed.");
        my_web3 = new Web3(new Web3.providers.HttpProvider(rpcUrl));
    } else {
        my_web3 = new Web3(web3.currentProvider); 
    }

    console.log(my_web3);
    // contract = web3.eth.contract(abi).at(contract_address);
    contract = new my_web3.eth.Contract(abi, contract_address);
    console.log("contract_address: " + contract_address);
    console.log(contract);

    // get the users address
    my_web3.eth.getAccounts((error, result) => {
        if(error) {
          console.log(error);
        } else if(result.length == 0) {
          console.log("You are not logged in");
        } else {
          account = result[0];
          contract.options.from = account;
        }
      }).catch((error) => {
        console.log("Error: " + error);
      });

    // read member variables values from constructor and display in web page 
    contract.methods.tokenName().call((error, result) => {
        if(error) {
            return console.log(error);
        }
        $('#tokenName').text(result);
    });

    contract.methods.tokenSymbol().call((error, result) => {
        if(error) {
            return console.log(error);
        }
        $('#tokenSymbol').text(result);
    });

    contract.methods.initialSupply().call((error, result) => {
        if(error) {
            return console.log(error);
        }
        $('#initialSupply').text(result);
    });

    // attach the event handler to the transfer button
    $('#transfer').click(setTransfer);

    // attach the event handler to the clear button
    $('#clear').click(setClear);

    // BrooklynToken.constructor(1000, "BrooklynToken","BKNTKN");
    // to: 0x14723a09acff6d2a60dcdf7aa4aff308fddc160c
    function setTransfer() {
        event.preventDefault();
        let to_address = $('#to_address').val();
        let transfer_amount = $('#transfer_amount').val();
        if (msg.style.display === "inline") {
            msg.style.display = "none";
        } 
        console.log("to_address, transfer_amount: ");
        console.log(to_address, transfer_amount);
        
        let token_symbol;
        contract.methods.transfer(to_address, transfer_amount).send(
            {gasPrice: web3.toWei(4.1, 'Gwei')},
            (error, result) => {
                if (msg.style.display === "none") {
                    msg.style.display = "inline";
                } 

                if(error) {
                    console.log("62. err: ");
                    console.log(result);
                    failMessage(msg);
                    return console.log(error);
                }
                console.log("txhash: " + result); 
                console.log("transferred " + transfer_amount + " " + token_symbol + " to " + to_address);

                $('#to_address').text("&nbsp;");
                $('#transfer_amount').text("&nbsp;");

                // display message in web page
                $('#transfer_amount_to').text(transfer_amount);
                $('#to_address_to').text(to_address);

                successMessage(transfer_amount, token_symbol, to_address);

            }
        ).catch((error) => {
            console.log("104. Error: " + error);
        });


        contract.methods.tokenSymbol().call((error, result) => {
            if(error) {
                return console.log(error);
            }
            // console.log(result);
            token_symbol = result;
            $('#token_symbol_to').text(token_symbol);
        })
    }

    function successMessage(transfer_amount, token_symbol, to_address){
        // console.log("transferred " + transfer_amount + " " + token_symbol + " to " + to_address);
        msg.style.color = "green";
        msg.innerHTML = "Success! Transferred " + transfer_amount + " " + token_symbol + " to " + to_address;
        console.log(msg.innerHTML);
    };

    function failMessage(msg){
        msg.style.color = "red";
        msg.innerHTML = "MetaMask: User denied transaction.";
    };

    function setClear(){
        msg.style.display = "none";
    }

});
