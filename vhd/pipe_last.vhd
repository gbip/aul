----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    17:49:58 05/07/2019 
-- Design Name: 
-- Module Name:    pipe_last - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use work.common.all;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity pipe_last is
Port ( 	  
			  -- CONTROL SIGNALS
			  en : in  STD_LOGIC;
           clk : in  STD_LOGIC;
           rst : in  STD_LOGIC;
           input : in p_last;
			  output : out p_last
			  );
end pipe_last;

architecture Behavioral of pipe_last is

begin
process
	begin
	wait until CLK'event and CLK='1';
		if RST='1' then 
			output.opcode<= (others => '0');
			output.firstOperand<= (others => '0');
			output.ual_readValue<= (others => '0');
			output.mem_readValue<= (others => '0');
			output.dataOperand<= (others => '0');
			output.secondRegData<= (others => '0');
			output.firstRegData<= (others => '0');
			else
			if EN='1' then
				output.opcode<= input.opcode;
				output.firstOperand <= input.firstOperand;
				output.ual_readValue <= input.ual_readValue;
				output.dataOperand <= input.dataOperand;
				output.secondRegData <= input.secondRegData;
				output.mem_readValue <= input.mem_readValue;
				output.firstRegData <= input.firstRegData;
			end if;
		end if;
	end process;

end Behavioral;

