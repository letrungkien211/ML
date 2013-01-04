## Copyright (C) 2013 letrungkien7
## 
## This program is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 2 of the License, or
## (at your option) any later version.
## 
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
## 
## You should have received a copy of the GNU General Public License
## along with Octave; see the file COPYING.  If not, see
## <http://www.gnu.org/licenses/>.

## report

## Author: letrungkien7 <letrungkien7@letrungkien7>
## Created: 2013-01-04

function [ ret ] = report (filename)

data = load(filename);
plot(data(:,1),data(:,2),data(:,1),data(:,3),data(:,1),data(:,4));
legend("Train Error", "Cross Validation Error", "Precision's rate");
xlabel("Size of training set");
  
endfunction
