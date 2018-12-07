# Harvard SC50 Final Project Design Document: BrooklynToken

This project is an HTML UI front-end implementation I wrote for an Ethereum Solidity dApp back-end program written by
my CareerDevs fellow student [Tim Wheeler](https://codesnippet.io/creating-your-own-cryptocurrency).
However, I had to refactor Tim's dApp so it would work when uploaded to [Ropsten TestNet Verified Contract](https://ropsten.etherscan.io/address/0xd74a0f3606dbc4ad636760a751ecacbbc294d288#code) site.

This project is an HTML UI front-end implementation for an Ethereum Solidity dApp back-end.  The front-end HTML User Interface is hosted on [Amazon S3](http://brooklyn-token-dapp.s3-website.us-east-2.amazonaws.com)  The back-end Solidity dApp is hosted on the [Ropsten Etherscan TestNet](https://ropsten.etherscan.io/address/0xd74a0f3606dbc4ad636760a751ecacbbc294d288#code)

You must have MetaMask browser plug-in installed in your Chrome Firefox or Opera browser for this blockchain app to work.
There are other browser plug-ins available for running blockchain dApps in your browser,
but MetaMask is by far the most popular and the one I recommend.
So if you don't have MetaMask installed, head on over to MetaMask.io and install it.

The Solidity part of this project is detailed in Tim Wheeler's excellent [tutorial](https://codesnippet.io/creating-your-own-cryptocurrency)
The smart contract, or dApp, was written and tested on the [Ethereum IDE online](https://remix.ethereum.org)
but that IDE is for development purposes only.

After writing and testing the code, I pasted it into the [Etherscan bytecode generator](https://ropsten.etherscan.io/verifyContract2k)
where it will live forever (presumably).  But I ran into a few issues getting it to run there, so I had to refactor some of Tim's code,
and eventually got it working.
