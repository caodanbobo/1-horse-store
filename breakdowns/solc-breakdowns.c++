//0x6080604052
// 34801561000f575f80fd5b506101438061001d5f395ff3fe608060405234801561000f575f80fd5b5060043610610034575f3560e01c8063cdfead2e14610038578063e026c01714610054575b5f80fd5b610052600480360381019061004d91906100ba565b610072565b005b61005c61007b565b60405161006991906100f4565b60405180910390f35b805f8190555050565b5f8054905090565b5f80fd5b5f819050919050565b61009981610087565b81146100a3575f80fd5b50565b5f813590506100b481610090565b92915050565b5f602082840312156100cf576100ce610083565b5b5f6100dc848285016100a6565b91505092915050565b6100ee81610087565b82525050565b5f6020820190506101075f8301846100e5565b9291505056fea264697066735822122034d1d927ef97d7c45fbf5937b48a42c74fc172a2114b1732e826129f388238b564736f6c63430008140033

// 3 sections:
//  1. Contract Creation Code
//  2. Runtime Code
//  3. Metadata

//1. Contract Creation Code

PUSH1 0x80          // Free Memory Pointer
PUSH1 0x40          //where the free memory pointer is stored
MSTORE              // store 0x80 at 0x40 in memory

// if someone sent value with the call revert
// otherwise, jump to continuie execution
CALLVALUE           //[msg.value]
DUP1                //[msg.value, msg.value]
ISZERO              //[msg.value==0, msg.value]
PUSH2 0x000f        //[0x000f, msg.value==0, msg.value]
JUMPI               //[msg.value]
PUSH0               //[0x00, msg.value]
DUP1                //[0x00, 0x00, msg.value]
REVERT              //[msg.value]

//sticks the runtime code on chain
JUMPDEST            //[msg.value]   JUMPDEST won't do anything, just a marker for JUMP/JUMPI
POP                 //[]   
PUSH2 0x0143        //[0x0143] length of runtime code
DUP1                //[0x0143, 0x0143]
PUSH2 0x001d        //[0x001d, 0x0143, 0x0143] offset where runtime code starts
PUSH0               //[0x00, 0x001d, 0x0143, 0x0143]
CODECOPY            //[0x0143] Memory:[runtime code]
PUSH0               //[0x00, 0x0143]
RETURN              //[] "RETURN" 实际上创建了合约, 除了CREATE/CREATE2, 合约可通过to为nil的transaction创建
INVALID             //[]

//2. Runtime Code
//[0x1d]
PUSH1 0x80
PUSH1 0x40
MSTORE

// if someone sent value with the call revert
CALLVALUE           //[msg.value]
DUP1                //[msg.value, msg.value]
ISZERO              //[msg.value==0, msg.value]
PUSH2 0x000f        //[0x000f, msg.value==0, msg.value]
JUMPI               //[msg.value]
PUSH0               //[0x00, msg.value]
DUP1                //[0x00, 0x00, msg.value]
REVERT              //[msg.value]    

JUMPDEST

//calldata是否有func selector
POP                 //[]
PUSH1 0x04          // [0x04]
CALLDATASIZE        // [calldatasize, 0x04]
LT                  // [calldatasize<4]
PUSH2 0x0034        // [0x0034, calldatasize<4]
JUMPI               // [] if calldatasize<4 jump to 0x34
//go to calldata_jump

PUSH0               // [0x00]
CALLDATALOAD        // [calldata[0:32], 0x00]
PUSH1 0xe0          // [0xe0, calldata[0:32], 0x00]
SHR                 // [calldata[0:4]] func selector 
DUP1                // [calldata[0:4], calldata[0:4]]
PUSH4 0xcdfead2e    // [0xcdfead2e, calldata[0:4], calldata[0:4]]
EQ                  // [calldata[0:4]==0xcdfead2e, calldata[0:4]]
PUSH2 0x0038        // [0x0038, calldata[0:4]==0xcdfead2e, calldata[0:4]]
JUMPI               // [calldata[0:4]] 
// if calldata[0:4]==0xcdfead2e jump to 0x38

DUP1                // [calldata[0:4], calldata[0:4]]
PUSH4 0xe026c017    // [0xe026c017, calldata[0:4], calldata[0:4]]
EQ                  // [calldata[0:4]==0xe026c017, calldata[0:4]]
PUSH2 0x0054        // [0x0054, calldata[0:4]==0xe026c017, calldata[0:4]]
JUMPI               // [calldata[0:4]] 
// if calldata[0:4]==0xe026c017 jump to 0x54

//calldata_jump
//revert
JUMPDEST
PUSH0
DUP1
REVERT

//updateHorseNumber jumpdest 1
JUMPDEST            // [calldata[0:4]] 
PUSH2 0x0052        // [0x0052, calldata[0:4]]
PUSH1 0x04          // [0x04, 0x0052, calldata[0:4]]
DUP1                // [0x04, 0x04, 0x0052, calldata[0:4]]
CALLDATASIZE        // [calldatasize, 0x04, 0x0052, calldata[0:4]]
SUB                 // [calldatasize-4, 0x0052, calldata[0:4]]
DUP2                // [0x0052, calldatasize-4, 0x0052, calldata[0:4]]
ADD                 // [0x0052+calldatasize-4, 0x0052, calldata[0:4]]
SWAP1               // [0x0052, 0x0052+calldatasize-4, calldata[0:4]]
PUSH2 0x004d        // [0x004d, 0x0052, 0x0052+calldatasize-4, calldata[0:4]]
SWAP2               // [0x0052+calldatasize-4, 0x0052, 0x004d, calldata[0:4]]
SWAP1               // [0x0052, 0x0052+calldatasize-4, 0x004d, calldata[0:4]]
PUSH2 0x00ba        // [0x00ba, 0x0052, 0x0052+calldatasize-4, 0x004d, calldata[0:4]]
JUMP                
// go to updateHorseNumber jumpdest 2

JUMPDEST
PUSH2 0x0072
JUMP
JUMPDEST
STOP
JUMPDEST
PUSH2 0x005c
PUSH2 0x007b
JUMP
JUMPDEST
PUSH1 0x40
MLOAD
PUSH2 0x0069
SWAP2
SWAP1
PUSH2 0x00f4
JUMP
JUMPDEST
PUSH1 0x40
MLOAD
DUP1
SWAP2
SUB
SWAP1
RETURN
JUMPDEST
DUP1
PUSH0
DUP2
SWAP1
SSTORE
POP
POP
JUMP
JUMPDEST
PUSH0
DUP1
SLOAD
SWAP1
POP
SWAP1
JUMP
JUMPDEST
PUSH0
DUP1
REVERT
JUMPDEST
PUSH0
DUP2
SWAP1
POP
SWAP2
SWAP1
POP
JUMP
JUMPDEST
PUSH2 0x0099
DUP2
PUSH2 0x0087
JUMP
JUMPDEST
DUP2
EQ
PUSH2 0x00a3
JUMPI
PUSH0
DUP1
REVERT
JUMPDEST
POP
JUMP

//updateHorseNumber jumpdest 4
JUMPDEST            // [0x0052, 0x0052+calldatasize-4, 0x00dc, 0x00, 0x00, 0x0052, 0x0052+calldatasize-4, 0x004d, calldata[0:4]]
PUSH0               // [0x00, 0x0052, 0x0052+calldatasize-4, 0x00dc, 0x00, 0x00, 0x0052, 0x0052+calldatasize-4, 0x004d, calldata[0:4]]
DUP2                // [0x0052, 0x00, 0x0052, 0x0052+calldatasize-4, 0x00dc, 0x00, 0x00, 0x0052, 0x0052+calldatasize-4, 0x004d, calldata[0:4]]
CALLDATALOAD        // [calldata[0:32], 0x0052, 0x00, 0x0052, 0x0052+calldatasize-4, 0x00dc, 0x00, 0x00, 0x0052, 0x0052+calldatasize-4, 0x004d, calldata[0:4]]
SWAP1               // [0x0052, calldata[0:32], 0x00, 0x0052, 0x0052+calldatasize-4, 0x00dc, 0x00, 0x00, 0x0052, 0x0052+calldatasize-4, 0x004d, calldata[0:4]]
POP                 // [calldata[0:32], 0x00, 0x0052, 0x0052+calldatasize-4, 0x00dc, 0x00, 0x00, 0x0052, 0x0052+calldatasize-4, 0x004d, calldata[0:4]]
PUSH2 0x00b4            
DUP2
PUSH2 0x0090
JUMP
JUMPDEST
SWAP3
SWAP2
POP
POP
JUMP

//updateHorseNumber jumpdest 2
//check if more calldata than just selector
JUMPDEST            // [0x0052, 0x0052+calldatasize-4, 0x004d, calldata[0:4]]
PUSH0               // [0x00, 0x0052, 0x0052+calldatasize-4, 0x004d, calldata[0:4]]
PUSH1 0x20          // [0x20, 0x00, 0x0052, 0x0052+calldatasize-4, 0x004d, calldata[0:4]]
DUP3                // [0x0052, 0x20, 0x00, 0x0052, 0x0052+calldatasize-4, 0x004d, calldata[0:4]]
DUP5                // [0x0052+calldatasize-4, 0x0052, 0x20, 0x00, 0x0052, 0x0052+calldatasize-4, 0x004d, calldata[0:4]]
SUB                 // [calldatasize-4, 0x20, 0x00, 0x0052, 0x0052+calldatasize-4, 0x004d, calldata[0:4]]
SLT                 // [calldatasize-4<0x20, 0x00, 0x0052, 0x0052+calldatasize-4, 0x004d, calldata[0:4]]
ISZERO              // [more_calldata_than_selector, 0x00, 0x0052, 0x0052+calldatasize-4, 0x004d, calldata[0:4]]
PUSH2 0x00cf        // [0x00cf, more_calldata_than_selector, 0x00, 0x0052, 0x0052+calldatasize-4, 0x004d, calldata[0:4]]
JUMPI               // [0x00, 0x0052, 0x0052+calldatasize-4, 0x004d, calldata[0:4]] if more_calldata_than_selector jump to 0xcf 
//go to updateHorseNumber jumpdest 3

PUSH2 0x00ce
PUSH2 0x0083
JUMP
JUMPDEST


//updateHorseNumber jumpdest 3
JUMPDEST            // [0x00, 0x0052, 0x0052+calldatasize-4, 0x004d, calldata[0:4]] if more_calldata_than_selector jump to 0xcf 
PUSH0               // [0x00, 0x00, 0x0052, 0x0052+calldatasize-4, 0x004d, calldata[0:4]]
PUSH2 0x00dc        // [0x00dc, 0x00, 0x00, 0x0052, 0x0052+calldatasize-4, 0x004d, calldata[0:4]]
DUP5                // [0x0052+calldatasize-4, 0x00dc, 0x00, 0x00, 0x0052, 0x0052+calldatasize-4, 0x004d, calldata[0:4]]
DUP3                // [0x00, 0x0052+calldatasize-4, 0x00dc, 0x00, 0x00, 0x0052, 0x0052+calldatasize-4, 0x004d, calldata[0:4]]
DUP6                // [0x0052, 0x00, 0x0052+calldatasize-4, 0x00dc, 0x00, 0x00, 0x0052, 0x0052+calldatasize-4, 0x004d, calldata[0:4]]
ADD                 // [0x0052, 0x0052+calldatasize-4, 0x00dc, 0x00, 0x00, 0x0052, 0x0052+calldatasize-4, 0x004d, calldata[0:4]]
PUSH2 0x00a6        // [0x00a6, 0x0052, 0x0052+calldatasize-4, 0x00dc, 0x00, 0x00, 0x0052, 0x0052+calldatasize-4, 0x004d, calldata[0:4]]
JUMP                // [0x0052, 0x0052+calldatasize-4, 0x00dc, 0x00, 0x00, 0x0052, 0x0052+calldatasize-4, 0x004d, calldata[0:4]]
//go updateHorseNumber jumpdest 4

JUMPDEST
SWAP2
POP
POP
SWAP3
SWAP2
POP
POP
JUMP
JUMPDEST
PUSH2 0x00ee
DUP2
PUSH2 0x0087
JUMP
JUMPDEST
DUP3
MSTORE
POP
POP
JUMP
JUMPDEST
PUSH0
PUSH1 0x20
DUP3
ADD
SWAP1
POP
PUSH2 0x0107
PUSH0
DUP4
ADD
DUP5
PUSH2 0x00e5
JUMP
JUMPDEST
SWAP3
SWAP2
POP
POP
JUMP
INVALID
LOG2
PUSH5 0x6970667358
INVALID
SLT
KECCAK256
CALLVALUE
INVALID
INVALID
INVALID
INVALID
SWAP8
INVALID
INVALID
PUSH0
INVALID
MSIZE
CALLDATACOPY
INVALID
DUP11
TIMESTAMP
INVALID
INVALID
INVALID
PUSH19 0xa2114b1732e826129f388238b564736f6c6343
STOP
ADDMOD
EQ
STOP
CALLER