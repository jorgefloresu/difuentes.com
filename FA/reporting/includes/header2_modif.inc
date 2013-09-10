<?php
/**********************************************************************
    Copyright (C) FrontAccounting, LLC.
	Released under the terms of the GNU General Public License, GPL, 
	as published by the Free Software Foundation, either version 3 
	of the License, or (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
    See the License here <http://www.gnu.org/licenses/gpl-3.0.html>.
***********************************************************************/

    // New version (without vertical lines)

//======================================================================
//	Modified for preferred layout
//	Rev: 0.1   Inserted comments, removed minor data
//======================================================================

	global $wo_types_array, $systypes_array;
	
// Set up some standards for the document
		$NumberOfColumns = 5;
// Set the position of the first line
		$this->row = $this->pageHeight - $this->topMargin;

		$upper = $this->row - 2 * $this->lineHeight;
		$lower = $this->bottomMargin + 2 * $this->lineHeight;
// Set up the positions of the graphics lines
		$iline1 = $upper - 1 * $this->lineHeight;
// The next three are the minor data horizontal lines
//		$iline2 = $iline1 - 8 * $this->lineHeight;
//		$iline3 = $iline2 - 1.5 * $this->lineHeight;
//		$iline4 = $iline3 - 1.5 * $this->lineHeight;
		$iline5 = $iline1 - 2.0 * $this->lineHeight;
		$iline6 = $iline5 - 1.5 * $this->lineHeight;
		$iline7 = $lower;
// Set the position of the RH side
		$right = $this->pageWidth - $this->rightMargin;
// Set the standard column widths
//		$width = ($right - $this->leftMargin) / 5;
		$width = ($right - $this->leftMargin) / $NumberOfColumns;
		$icol = $this->pageWidth / 2;
		$ccol = $this->cols[0] + 4;
		$c2col = $ccol + 60;
		$ccol2 = $icol / 2;
		$mcol = $icol + 8;
		$mcol2 = $this->pageWidth - $ccol2;
		$cols = count($this->cols);

// Set up the graphics
// Horizontal line after company details (really two lines in one)
//		$this->SetDrawColor(205, 205, 205);
//		$this->Line($iline1, 3);
//		$this->SetDrawColor(128, 128, 128);
//		$this->Line($iline1);

// Rectangle and dividing line around the minor data
//		$this->rectangle($this->leftMargin, $iline2, $right - $this->leftMargin, $iline2 - $iline3, "F", null, array(222, 231, 236));   
//		$this->Line($iline2);
//		$this->Line($iline3);
//		$this->Line($iline4);
//		$this->rectangle($this->leftMargin, $iline5, $right - $this->leftMargin, $iline5 - $iline6, "F", null, array(222, 231, 236));   

// Major dividing lines on the invoice
//		$this->Line($iline5);
//		$this->Line($iline6);
//		$this->Line($iline7);

// These are the six vertical lines for the five minor data boxes
//		$this->LineTo($this->leftMargin, $iline2 ,$this->leftMargin, $iline4);
//		$col = $this->leftMargin;
//		for ($i = 0; $i < 5; $i++)
//		{
//			$this->LineTo($col += $width, $iline2,$col, $iline4);
//		}	
//		$this->LineTo($right, $iline2 ,$right, $iline4);

// And the left and right bars for the main data
//		$this->LineTo($this->leftMargin, $iline5 ,$this->leftMargin, $iline7);
//		$this->LineTo($this->cols[$cols - 2] + 4, $iline5 ,$this->cols[$cols - 2] + 4, $iline7);
//		$this->LineTo($right, $iline5 ,$right, $iline7);

		$this->NewLine();

// All the neat lines are now drawn
// Look out chaps - you can have either the company logo or its name.  Make sure you include the name in the logo
		//if ($this->company['coy_logo'] != '')
		//{
		//	$logo = $comp_path .'/'. user_company() . "/images/" . $this->company['coy_logo'];
			//$this->AddImage($logo, $ccol, $this->row, 0, 40);
		//}
		//else
		//{
			$this->fontSize += 2;
			$this->Font('bold');
			//$this->Text($ccol, $this->company['coy_name'], $icol);
                        $this->Text(15, "Distribuidora DASAL");
			$this->Font();
			$this->fontSize -= 2;
		//}
//Write out what type of document this is (INVOICE etc) (The colour is grey) (The color is gray)
		$this->SetTextColor(190, 190, 190);
		$this->fontSize += 10;
		$this->Font('bold');
		//$this->TextWrap($mcol, $this->row, $this->pageWidth - $this->rightMargin - $mcol - 20, $this->title, 'right');
		$this->Font();
		$this->fontSize -= 10;
// and now the postal address (in black) (We added the country to the end of the address)
		//$this->NewLine();
		$this->SetTextColor(0, 0, 0);
		$adrline = $this->row;
		//$this->TextWrapLines($ccol, $icol, $this->company['postal_address'].".   ".$this->company['domicile']);
		//$this->NewLine();
		$this->Font('italic');
		if ($this->company['phone'] != "")
		{
			//$this->Text($ccol, _("Phone").":", $c2col);
			//$this->Text($ccol + 35, $this->company['phone']);
//			$this->Text($c2col, $this->company['phone'], $mcol);
			//$this->NewLine();
		}	
		if ($this->company['fax'] != "")
		{
			//$this->Text($ccol, _("Fax").":", $c2col);
			//$this->Text($ccol + 35, $this->company['fax']);
			//$this->NewLine();
		}	
		if ($this->company['email'] != "")
		{
			//$this->Text($ccol, _("Email").":", $c2col);

			$url = "mailto:" . $this->company['email'];
			$this->SetTextColor(0, 0, 255);
			//$this->Text($ccol + 35, $this->company['email']);
			$this->SetTextColor(0, 0, 0);
			$this->addLink($url, $c2col, $this->row, $mcol, $this->row + $this->lineHeight);

			$this->NewLine();
		}	
// Here we (re)move the domicile, but add a new line in its place
//		if (($doctype == ST_SALESINVOICE || $doctype == ST_STATEMENT) && $this->company['domicile'] != "")
//		{
//			$this->Text($ccol, $doc_Domicile, $c2col);
//			$this->Text($c2col, $this->company['domicile'], $mcol);
//			$this->NewLine();
//		}
		//$this->NewLine();
		$this->Font();
		//$this->row = $adrline;
//Position the date, invoice number (and moved VAT/GST number)
                
		//$this->NewLine(2);
		//$this->Text(10, $doc_Date.":");
                $ahora = $this->row;
                $this->row = $this->row - 15;
		if ($doctype == ST_SALESQUOTE || $doctype == ST_PURCHORDER || $doctype == ST_SALESORDER)
			$this->Text($mcol + 180, sql2date($myrow['ord_date']));
		elseif ($doctype == ST_WORKORDER)	
			$this->Text($mcol + 180, sql2date($myrow['date_']));
		else
			//old: $this->Text($mcol + 115, sql2date($myrow['tran_date']));
                        $this->Text(15, "Fecha:".sql2date($myrow['tran_date']));
                $this->row = $ahora;
		//$this->NewLine();
		//$this->Text($mcol + 100, $doc_Invoice_no.":");
		if ($doctype == ST_SALESQUOTE || $doctype == ST_PURCHORDER || $doctype == ST_SALESORDER) // QUOTE, PO or SO
		{
		//	if ($print_invoice_no == 1)
		//		$this->Text($mcol + 180, $myrow['order_no']);
		//	else	
		//		$this->Text($mcol + 180, $myrow['reference']);
		}		
		elseif ($doctype == ST_WORKORDER)	
			$this->Text($mcol + 180, $myrow['id']);
		else if (isset($myrow['trans_no']) && isset($myrow['reference'])) // INV/CRE/STA
		{
		//	if ($print_invoice_no == 1)
		//		$this->Text($mcol + 180, $myrow['trans_no']);
		//	else
		//		$this->Text($mcol + 180, $myrow['reference']);
		}
		//$this->NewLine(2);

// We moved the GST/VAT number
		if ($this->company['gst_no'] != "")
		{
// The value for $doc_Our_VAT_no can be found in ~/reporting/includes/doctext2.inc
			//$this->Text($mcol + 100, $doc_Our_VAT_no.":");
			//$this->Text($mcol + 180, $this->company['gst_no']);
			//$this->NewLine();
		}
// We moved the customer ref (etc) up here               
		//$this->Text($mcol + 100, $doc_Customers_Ref.":");
		//if ($doctype == ST_PURCHORDER || $doctype == ST_SUPPAYMENT)
		//	$this->Text($mcol + 180, $myrow['supp_account_no']);
		//elseif ($doctype == ST_WORKORDER)
		//	$this->Text($mcol + 180, $myrow['wo_ref']);
		//elseif (isset($sales_order["customer_ref"]))
		//	$this->Text($mcol + 180, $sales_order["customer_ref"]);
		//elseif (isset($myrow["debtor_ref"]))
		//	$this->Text($mcol + 180, $myrow["debtor_ref"]);

		if ($this->pageNumber > 1 && !strstr($this->filename, "Bulk"))
			$this->Text($this->endLine - 35, _("Page") . ' ' . $this->pageNumber);
		//$this->row = $iline1 - $this->lineHeight;
		$this->fontSize -= 4;
		//$this->Text($ccol, $doc_Charge_To, $icol);
		//$this->Text($mcol, $doc_Delivered_To);

// We wanted a slightly larger font because the address goes in a windowed envelope
		$this->fontSize += 6;

		$this->row = $this->row - $this->lineHeight - 20;

		$temp = $this->row;
		if ($doctype == ST_SALESQUOTE || $doctype == ST_SALESORDER)
		{
			//$this->Text($ccol, $myrow['name'], $icol);
		}
		elseif ($doctype == ST_WORKORDER)
		{
			$this->Text($ccol, $myrow['location_name'], $icol);
			$this->NewLine();
			$this->TextWrapLines($ccol, $icol - $ccol, $myrow['delivery_address']);
		}
		else
		{
			if ($doctype == ST_PURCHORDER || $doctype == ST_SUPPAYMENT) {
				$name = $myrow['supp_name'];
				$addr = $myrow['address'];
			} else {
				if (trim($branch['br_address']) != '') {
					$name = $branch['br_name'];
					$addr = $branch['br_address'];
				} else {
					$name = $myrow['DebtorName'];
					$addr = $myrow['address'];
				}
			}
                        //$this->Text($ccol + 45, $name, $icol);
			//old: $this->Text($ccol + 45, $name);
                        $this->Text($ccol, $name, $icol);
			$this->NewLine();
			//$this->TextWrapLines($ccol, $icol - $ccol, $addr);
                        //old: $this->Text($ccol + 45, $addr, $icol);
                        $this->Text($ccol, $addr);
                        //$this->Text($ccol + 45, $addr);
                        
                        
		}
		if ($sales_order != NULL)
		{
			$this->row = $temp;
			if ($doctype != ST_SUPPAYMENT && isset($sales_order['deliver_to']))
			{
				//$this->Text($mcol, $sales_order['deliver_to']);
				//$this->NewLine();
			}	
			// if you need the company name in purchase order then write it as first line in location addresss.	
			//if ($doctype != ST_SUPPAYMENT && isset($sales_order['delivery_address']))
			//	$this->TextWrapLines($mcol, $this->rightMargin - $mcol, $sales_order['delivery_address']);
		}
// And restore the font to normal
		$this->fontSize -= 2;
// The only thing we want is the customer ref so we kill all this (we also moved the customer ref up the page)
//		$this->row = $iline2 - $this->lineHeight - 1;
//		$col = $this->leftMargin;
//		$this->TextWrap($col, $this->row, $width, $doc_Customers_Ref, 'C');
//		$col += $width;
//		$this->TextWrap($col, $this->row, $width, $doc_Our_Ref, 'C');
//		$col += $width;
//		$this->TextWrap($col, $this->row, $width, $doc_Your_VAT_no, 'C');
//		$col += $width;
//		if ($doctype == ST_SALESINVOICE)
//			$this->TextWrap($col, $this->row, $width, $doc_Delivery_no, 'C');
//		else
//			$this->TextWrap($col, $this->row, $width, $doc_Our_Order_No, 'C');
//		$col += $width;
//		$this->TextWrap($col, $this->row, $width, $doc_Due_Date, 'C');
//		$this->row = $iline3 - $this->lineHeight - 1;
//		$col = $this->leftMargin;
//		$col += $width;	
//		if ($branch != null)
//		{
//			$id = $branch['salesman'];
//			$sql = "SELECT salesman_name  FROM ".TB_PREF."salesman WHERE salesman_code='$id'";
//			$result = db_query($sql,"could not get sales person");
//			$row = db_fetch($result);
//			$this->TextWrap($col, $this->row, $width, $row['salesman_name'], 'C');
//		}		
//		elseif ($doctype == ST_SUPPAYMENT || $doctype == ST_CUSTPAYMENT)
//			$this->TextWrap($col, $this->row, $width, $systypes_array[$myrow["type"]], 'C');
//		elseif ($doctype == ST_WORKORDER)
//			$this->TextWrap($col, $this->row, $width, $wo_types_array[$myrow["type"]], 'C');
//		$col += $width;	
//		if ($doctype == ST_WORKORDER)
//			$this->TextWrap($col, $this->row, $width, $myrow["StockItemName"], 'C');
//		elseif ($doctype != ST_PURCHORDER && isset($myrow['tax_id']))
//			$this->TextWrap($col, $this->row, $width, $myrow['tax_id'], 'C');
//		$col += $width;	
//		if ($doctype == ST_SALESINVOICE)
//		{
//			$deliveries = get_parent_trans(ST_SALESINVOICE, $myrow['trans_no']);
//			$line = "";
//			foreach ($deliveries as $delivery)
//			{
//				if ($print_invoice_no == 0)
//				{
//					$ref = get_reference(ST_CUSTDELIVERY, $delivery);
//					if ($ref)
//						$delivery = $ref;
//				}		
//				if ($line == "")
//					$line .= "$delivery";
//				else
//					$line .= ",$delivery";
//			}		
//			$this->TextWrap($col, $this->row, $width, $line, 'C');
//		}
//		elseif ($doctype == ST_CUSTDELIVERY)
//		{
//			$ref = $myrow['order_'];
//			if ($print_invoice_no == 0)
//			{
//				$ref = get_reference(ST_SALESORDER, $myrow['order_']);
//				if (!$ref)
//					$ref = $myrow['order_'];
//			}		
//			$this->TextWrap($col, $this->row, $width, $ref, 'C');
//		}
//		elseif ($doctype == ST_WORKORDER)
//			$this->TextWrap($col, $this->row, $width, $myrow["location_name"], 'C');
//		elseif (isset($myrow['order_']) && $myrow['order_'] != 0)
//			$this->TextWrap($col, $this->row, $width, $myrow['order_'], 'C');
//		$col += $width;	
//		if ($doctype == ST_SALESORDER || $doctype == ST_SALESQUOTE)
//			$this->TextWrap($col, $this->row, $width, sql2date($myrow['delivery_date']), 'C');
//		elseif ($doctype == ST_WORKORDER)	
//			$this->TextWrap($col, $this->row, $width, $myrow["units_issued"], 'C');
//		elseif ($doctype != ST_PURCHORDER && $doctype != ST_CUSTCREDIT && $doctype != ST_CUSTPAYMENT &&
//			$doctype != ST_SUPPAYMENT && isset($myrow['due_date']))
//			$this->TextWrap($col, $this->row, $width, sql2date($myrow['due_date']), 'C');
//		if (!isset($packing_slip) || $packing_slip == 0)
// End of minor data
// Main body headers
		//$this->row = $iline5 - $this->lineHeight - 20;
                $this->row = $iline5 - $this->lineHeight;
                
		$this->Font('bold');
		$count = count($this->headers);
		$this->cols[$count] = $right - 3;
		for ($i = 0; $i < $count; $i++)
			//$this->TextCol($i, $i + 1, $this->headers[$i], -2);
		$this->Font();

// End of Main body headers
		$this->Font('italic');
		//$this->row = $iline7 - $this->lineHeight - 20;
		if ($doctype != ST_WORKORDER)
			//$this->TextWrap($ccol, $this->row, $right - $ccol, $doc_Please_Quote . " - " . $myrow['curr_code'], 'C');
		$this->row -= $this->lineHeight;

		if (isset($bankaccount['bank_name']))
		{
			$txt = $doc_Bank . ": ".$bankaccount['bank_name']. ", " . $doc_Bank_Account . ": " . $bankaccount['bank_account_number'];
			//$this->TextWrap($ccol, $this->row, $right - $ccol, $txt, 'C');
			$this->row -= $this->lineHeight;
		}	
		if ($doctype == ST_SALESINVOICE && $branch['disable_branch'] > 0) // payment links
		{
			if ($branch['disable_branch'] == 1)
			{
				$amt = number_format($myrow["ov_freight"] + $myrow["ov_gst"] +	$myrow["ov_amount"], user_price_dec());
				$txt = $doc_Payment_Link . " PayPal: ";
				$name = urlencode($this->title . " " . $myrow['reference']);
				$url = "https://www.paypal.com/xclick/business=" . $this->company['email'] . "&item_name=" .
					$name . "&amount=" . $amt . "&currency_code=" . $myrow['curr_code'];
				$this->fontSize -= 2;
				//$this->TextWrap($ccol, $this->row, $right - $ccol, $txt, 'C');
				$this->row -= $this->lineHeight;
				$this->SetTextColor(0, 0, 255);
				$//this->TextWrap($ccol, $this->row, $right - $ccol, $url, 'C');
				$this->SetTextColor(0, 0, 0);
				$this->addLink($url, $ccol, $this->row, $this->pageWidth - $this->rightMargin, $this->row + $this->lineHeight);
				$this->fontSize += 2;
				$this->row -= $this->lineHeight;
			}
		}
// We moved the payment terms to the bottom - ie to here
		{
			$this->row -= ($this->lineHeight);
			if ($doctype == ST_WORKORDER)
				$str = sql2date($myrow["required_by"]);
			else
			{
				$id = $myrow['payment_terms'];
				$sql = "SELECT terms FROM ".TB_PREF."payment_terms WHERE terms_indicator='$id'";
				$result = db_query($sql,"could not get paymentterms");
				$row = db_fetch($result);
				$str = $row["terms"];
			}	
			$this->Font('italic');
			//$this->TextWrap($ccol, $this->row, $right-$ccol, $doc_Payment_Terms . ":  " . $str);
			$this->Font();
		}
		if ($doc_Extra != "")
		{
			//$this->TextWrap($ccol, $this->row, $right - $ccol, $doc_Extra.":", 'C');
			$this->row -= $this->lineHeight;
		}
		if ($this->params['comments'] != '')
		{
			//$this->TextWrap($ccol, $this->row, $right - $ccol, $this->params['comments'], 'C');
			$this->row -= $this->lineHeight;
		}
		if (($doctype == ST_SALESINVOICE || $doctype == ST_STATEMENT) && $this->company['legal_text'] != "") 
		{
			$this->row -= $this->lineHeight;
			//$this->TextWrap($ccol, $this->row, $right - $ccol, $this->company['legal_text']);
		}
		$this->Font();
		$temp = $iline6 - $this->lineHeight + 10;
?>