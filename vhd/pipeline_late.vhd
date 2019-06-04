----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    10:23:16 04/18/2019 
-- Design Name: 
-- Module Name:    pipeline_late - Behavioral 
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

entity pipeline_late is
 Port ( 	  
			  -- CONTROL SIGNALS
			  en : in  STD_LOGIC;
           clk : in  STD_LOGIC;
           rst : in  STD_LOGIC;
           input : in p_late;
			  output : out p_late
			  );
end pipeline_late;

architecture Behavioral of pipeline_late is
begin

	process
	begin
	wait until CLK'event and CLK='1';
		if RST='1' then 
			output.opcode<= (others => '0');
			output.reg<= (others => '0');
			output.val<= (others => '0');
			output.d1<= (others => '0');
			output.d2<= (others => '0');
			output.flags<= (others => '0');
			output.ual_output<= (others => '0');
			else
			if EN='1' then
				output.opcode<= input.opcode;
				output.reg<= input.reg;
				output.val<= input.val;
				output.d1<= input.d1;
				output.d2<= input.d2;
				output.flags<= input.flags;
				output.ual_output <= input.ual_output;
			end if;
		end if;
	end process;
end Behavioral;
