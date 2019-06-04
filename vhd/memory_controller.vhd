----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    17:08:22 05/07/2019 
-- Design Name: 
-- Module Name:    memory_controller - Behavioral 
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
use IEEE.NUMERIC_STD.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity memory_controller is
Port (	  clk : in  STD_LOGIC;
           en : in  STD_LOGIC;
           rst : in  STD_LOGIC;
           w : in  STD_LOGIC;
           data : in  STD_LOGIC_VECTOR (31 downto 0);
           addr : in  STD_LOGIC_VECTOR (31 downto 0);
			  data_out : out STD_LOGIC_VECTOR (31 downto 0));
end memory_controller;

architecture Behavioral of memory_controller is
	type MEMORY is array (16384 to 16400) of STD_LOGIC_VECTOR (31 downto 0); --FA0 to 1004
	signal mem : MEMORY := (others => (others => '0'));
begin

process
begin
	wait until CLK'event and CLK='1';
		if RST='1' then 
			mem <= (others => (others => '0'));
		else if en='1' then
			if w='1' then
				mem(to_integer(unsigned(addr))) <= data;
			end if;
			end if;
		end if;
end process;

data_out <= mem(to_integer(unsigned(addr))) when en='1' else (others => '0');


end Behavioral;

