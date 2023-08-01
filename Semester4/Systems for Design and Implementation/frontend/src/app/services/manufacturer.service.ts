import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Manufacturer } from '../model/Manufacturer';
import { Observable } from 'rxjs';
import { GenericPage } from '../model/GenericPage';
import { environment } from 'src/environments/environment';
import { Product } from '../model/Product';
import { ManufacturerProductCountDTO } from '../dto/ManufacturerProductCountDTO';
import { ManufacturerCreate } from '../model/ManufacturerCreate';

@Injectable({
  providedIn: 'root'
})

export class ManufacturerService {

  constructor(private http: HttpClient) { }

  getAllManufacturers(pageNumber: number, pageSize: number): Observable<GenericPage<Manufacturer>> {
    return this.http.get<GenericPage<Manufacturer>>(environment.apiURL + "/manufacturers" + `?pageNumber=${pageNumber}` + `&pageSize=${[pageSize]}`);
  }

  getManufacturersReviewCountPage(pageNumber: number, pageSize: number): Observable<GenericPage<ManufacturerProductCountDTO>> {
    return this.http.get<GenericPage<ManufacturerProductCountDTO>>(environment.apiURL + "/manufacturer-product-counts" + `?pageNumber=${pageNumber}` + `&pageSize=${[pageSize]}`);
  }

  getAllProductsForManufacturer(manufacturerId: number, pageNumber: number, pageSize: number): Observable<GenericPage<Product>> {
    return this.http.get<GenericPage<Product>>(environment.apiURL + "/manufacturers" + `/${manufacturerId}` + "/products" + `?pageNumber=${pageNumber}` + `&pageSize=${[pageSize]}`);
  }

  getManufacturerById(id: number): Observable<Manufacturer> {
    return this.http.get<Manufacturer>(environment.apiURL + "/manufacturers/" + id.toString());
  }

  editManufacturer(manufacturer: Manufacturer): Observable<any>{
    return this.http.patch(environment.apiURL + "/manufacturers/" + manufacturer.id.toString(), manufacturer);
  }

  createManufacturer(manufacturer: ManufacturerCreate): Observable<any>{
    return this.http.post(environment.apiURL + "/manufacturers", manufacturer);
  }

  deleteManufacturer(id: number): Observable<any> {
    return this.http.delete(environment.apiURL + "/manufacturers/" + id.toString());
  }

  getManufacturerCountStatistic(pageNumber: number, pageSize: number): Observable<GenericPage<ManufacturerProductCountDTO>> {
    return this.http.get<GenericPage<ManufacturerProductCountDTO>>(environment.apiURL + "/manufacturers/sorted-by-products" + `?pageNumber=${pageNumber}` + `&pageSize=${[pageSize]}`);
  }
}
