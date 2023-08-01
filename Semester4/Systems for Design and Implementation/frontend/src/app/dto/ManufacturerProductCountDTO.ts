import { Manufacturer } from "../model/Manufacturer";

export interface ManufacturerProductCountDTO{
    manufacturerDTO: Manufacturer,
    productCount: number
}